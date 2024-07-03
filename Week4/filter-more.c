// not passing yet

#include "helpers.h"
#include <math.h>

// Function Prototypes
int roundAndHexCap (int num);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int average;
            average = round((image[i][k].rgbtRed + image[i][k].rgbtBlue + image[i][k].rgbtGreen) / 3);
            image[i][k].rgbtRed = average;
            image[i][k].rgbtBlue = average;
            image[i][k].rgbtGreen = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width / 2; k++)
        {
            RGBTRIPLE temp = image[i][k];
            image[i][k] = image[i][width - k - 1];
            image[i][width - k - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of the image to pull the unchanged values from
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            copy[i][k] = image[i][k];
        }
    }
    // Go through every pixel in the original image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int averageRed = 0;
            int averageBlue = 0;
            int averageGreen = 0;
            float validPosition = 0;
            // we look at a blurbox around the current pixel in the original image. 3x3 square
            for (int blurboxHeightPosition = x - 1; blurboxHeightPosition < x + 2; blurboxHeightPosition++)
            {
                for (int blurboxWidthPosition = y - 1; blurboxWidthPosition < y + 2; blurboxWidthPosition++)
                {
                    // if not outside the original image
                    if(blurboxHeightPosition >= 0 && blurboxHeightPosition < height && blurboxWidthPosition >= 0 && blurboxWidthPosition < width)
                    {
                        // add each of the channels together so we can average them to filli n the imddle squares values
                        averageRed += copy[blurboxHeightPosition][blurboxWidthPosition].rgbtRed;
                        averageBlue += copy[blurboxHeightPosition][blurboxWidthPosition].rgbtBlue;
                        averageGreen += copy[blurboxHeightPosition][blurboxWidthPosition].rgbtGreen;
                        validPosition++;
                    }
                }
            }
            image[x][y].rgbtRed = round(averageRed / validPosition);
            image[x][y].rgbtBlue = round(averageBlue / validPosition);
            image[x][y].rgbtGreen = round(averageGreen / validPosition);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int gxKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // make a copy of the initial image so we can work from an unfiltered copy.
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            copy[i][k] = image[i][k];
        }
    }
    /////////////////////////////////////////////////////////////////

    // go through every pixel in the image.
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // We will reset for each new pixel in the image we're looking at.
            int sunRedGx = 0;
            int sumRedGy = 0;
            int sumBlueGx = 0;
            int sumBlueGy = 0;
            int sumGreenGx = 0;
            int sumGreenGy = 0;
            for (int sobelHeightPosition = -1; sobelHeightPosition < 2; sobelHeightPosition++)
            {
                for (int sobelWidthPosition = 1; sobelWidthPosition < 2;sobelWidthPosition++)
                {
                    /*  Gx & Gy = for the nine pixels that form a 3x3 box around the pixel,get color channel
                        multiply them each by the corresponding value in the kernel,
                        and take the sum of the resulting values.
                        Set original image color channel = square root of Gx^2 + Gy^2.
                    */

                    sunRedGx += copy[x + sobelHeightPosition][y + sobelWidthPosition].rgbtRed * gxKernel[sobelHeightPosition][sobelWidthPosition];
                    sumRedGy += copy[x + sobelHeightPosition][y + sobelWidthPosition].rgbtRed * gyKernel[sobelHeightPosition][sobelWidthPosition];

                    sumBlueGx += copy[x + sobelHeightPosition][y + sobelWidthPosition].rgbtBlue * gxKernel[sobelHeightPosition][sobelWidthPosition];
                    sumBlueGy += copy[x + sobelHeightPosition][y + sobelWidthPosition].rgbtBlue * gyKernel[sobelHeightPosition][sobelWidthPosition];

                    sumGreenGx += copy[x + sobelHeightPosition][y + sobelWidthPosition].rgbtGreen * gxKernel[sobelHeightPosition][sobelWidthPosition];
                    sumGreenGy += copy[x + sobelHeightPosition][y + sobelWidthPosition].rgbtGreen * gyKernel[sobelHeightPosition][sobelWidthPosition];
                }
            }
            image[x][y].rgbtRed = roundAndHexCap(sqrt(sunRedGx * sunRedGx + sumRedGy * sumRedGy));
            image[x][y].rgbtBlue = roundAndHexCap(sqrt(sumBlueGx * sumBlueGx + sumBlueGy * sumBlueGy));
            image[x][y].rgbtGreen = roundAndHexCap(sqrt(sumGreenGx * sumGreenGx + sumGreenGy * sumGreenGy));
        }
    }
}

int roundAndHexCap (int num)
{
    return (num > 255) ? 255: round(num);
}

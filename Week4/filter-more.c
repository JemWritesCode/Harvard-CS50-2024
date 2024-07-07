// Passes check50 cs50/problems/2024/x/filter/more

#include "helpers.h"
#include <math.h>

// Function Prototypes
float roundAndHexCap(float num);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int average;
            // Divide by 3.0 so that it uses float instead of int.
            average = round((image[i][k].rgbtRed + image[i][k].rgbtBlue + image[i][k].rgbtGreen) / 3.0);
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
        // Divide width by 2 because it's already reflected once you're halfway through the image.
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
                    if (blurboxHeightPosition >= 0 && blurboxHeightPosition < height &&
                        blurboxWidthPosition >= 0 && blurboxWidthPosition < width)
                    {
                        // add each of the channels together so we can average them to fill in the middle squares values
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
    int gxKernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
        };
    int gyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // make a copy of the initial image so we can work from an unfiltered copy.
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            copy[i][k] = image[i][k];
        }
    }

    // go through every pixel in the image.
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // We will reset for each new pixel in the image we're looking at.
            int sumRedGx = 0;
            int sumRedGy = 0;
            int sumBlueGx = 0;
            int sumBlueGy = 0;
            int sumGreenGx = 0;
            int sumGreenGy = 0;
            for (int sobelHeightPosition = -1; sobelHeightPosition < 2; sobelHeightPosition++)
            {
                for (int sobelWidthPosition = -1; sobelWidthPosition < 2;sobelWidthPosition++)
                {
                    /*  Gx & Gy = for the nine pixels that form a 3x3 box around the pixel,get color channel
                        multiply them each by the corresponding value in the kernel,
                        and take the sum of the resulting values.
                        Set original image color channel = square root of Gx^2 + Gy^2.
                    */
                   if (x + sobelWidthPosition >= 0 && x + sobelWidthPosition < width && y + sobelHeightPosition >= 0 && y + sobelHeightPosition < height)
                   {
                        sumRedGx += copy[x + sobelWidthPosition][y + sobelHeightPosition].rgbtRed * gxKernel[sobelWidthPosition +1][sobelHeightPosition +1];
                        sumRedGy += copy[x + sobelWidthPosition][y + sobelHeightPosition].rgbtRed * gyKernel[sobelWidthPosition +1][sobelHeightPosition +1];

                        sumBlueGx += copy[x + sobelWidthPosition][y + sobelHeightPosition].rgbtBlue * gxKernel[sobelWidthPosition +1][sobelHeightPosition +1];
                        sumBlueGy += copy[x + sobelWidthPosition][y + sobelHeightPosition].rgbtBlue * gyKernel[sobelWidthPosition +1][sobelHeightPosition +1];

                        sumGreenGx += copy[x + sobelWidthPosition][y + sobelHeightPosition].rgbtGreen * gxKernel[sobelWidthPosition +1][sobelHeightPosition +1];
                        sumGreenGy += copy[x + sobelWidthPosition][y + sobelHeightPosition].rgbtGreen * gyKernel[sobelWidthPosition +1][sobelHeightPosition +1];
                   }
                                }
            }
            image[x][y].rgbtRed = roundAndHexCap(sqrt(sumRedGx * sumRedGx + sumRedGy * sumRedGy));
            image[x][y].rgbtBlue = roundAndHexCap(sqrt(sumBlueGx * sumBlueGx + sumBlueGy * sumBlueGy));
            image[x][y].rgbtGreen = roundAndHexCap(sqrt(sumGreenGx * sumGreenGx + sumGreenGy * sumGreenGy));
        }
    }
}

float roundAndHexCap (float num)
{
    num = round(num);
    return (num > 255) ? 255: num;
}

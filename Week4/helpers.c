// passing check50

#include "helpers.h"
#include <math.h>

// Limit a number to no larger than 255
int limitHex(int number);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = 0;
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = limitHex(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));
            int sepiaGreen = limitHex(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            int sepiaBlue = limitHex(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// ensure the number is not over 255
int limitHex(int number)
{
    return (number > 255) ? 255 : number;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // only need to swap up til half the width, because then everything is already swapped.
        for (int k = 0; k < width /2; k++)
        {
            RGBTRIPLE temp = image[i][k]; // the value of the current pixel
            // width-1 would get you the last pixel in current row. because we start array at 0.
            // k will reflect how far we are in from the front because we need to equally reflect from the end
            image[i][k] = image[i][width - 1 - k];
            image[i][width - 1 - k] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image to read the unfiltered pixels from.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            copy[i][k] = image[i][k];
        }
    }
    ////////////////////////////////////////////
    // Filter the pixels in the original image.
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int redAverage = 0;
            int blueAverage = 0;
            int greenAverage = 0;
            float validPositionCount = 0;
            // start looping through the box around the current pixel. -1 will start one row above and one column behind.
            for(int blurBoxHeightPosition = x - 1; blurBoxHeightPosition < x + 2; blurBoxHeightPosition++)
            {
                for (int blurBoxWidthPosition = y -1; blurBoxWidthPosition < y + 2; blurBoxWidthPosition++)
                {
                    // don't go outside the original image.
                    if(blurBoxHeightPosition >= 0 && blurBoxHeightPosition < height && blurBoxWidthPosition >= 0 && blurBoxWidthPosition < width)
                    {
                        redAverage += copy[blurBoxHeightPosition][blurBoxWidthPosition].rgbtRed;
                        blueAverage += copy[blurBoxHeightPosition][blurBoxWidthPosition].rgbtBlue;
                        greenAverage += copy[blurBoxHeightPosition][blurBoxWidthPosition].rgbtGreen;
                        validPositionCount++;
                    }
                }
            }
            image[x][y].rgbtRed = round(redAverage / validPositionCount);
            image[x][y].rgbtBlue = round(blueAverage / validPositionCount);
            image[x][y].rgbtGreen = round(greenAverage / validPositionCount);
            }
    }
}

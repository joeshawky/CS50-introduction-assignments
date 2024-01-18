#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp = image[i][j];
            int average = roundf((tmp.rgbtBlue + tmp.rgbtGreen + tmp.rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = sepiaBlue <= 255 ? sepiaBlue : 255;
            image[i][j].rgbtGreen = sepiaGreen <= 255 ? sepiaGreen : 255;
            image[i][j].rgbtRed = sepiaRed <= 255 ? sepiaRed : 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE rgb_vals[width];

        for (int j = 0; j < width; j++)
        {
            rgb_vals[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][width - j - 1] = rgb_vals[j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avgBlue;
    int avgGreen;
    int avgRed;

    RGBTRIPLE imageCopy[height][width];

    memcpy(imageCopy, image, sizeof(RGBTRIPLE) * height * width);

    int totalRed;
    int totalBlue;
    int totalGreen;
    float counter;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRed = 0;
            totalBlue = 0;
            totalGreen = 0;
            counter = 0;
            if (i == 0 && j == 0)
            {
                // top left corner
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        totalRed += imageCopy[i + k][j + l].rgbtRed;
                        totalBlue += imageCopy[i + k][j + l].rgbtBlue;
                        totalGreen += imageCopy[i + k][j + l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else if (i == 0 && j == width - 1)
            {
                // top right corner
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        totalRed += imageCopy[i + k][j - l].rgbtRed;
                        totalBlue += imageCopy[i + k][j - l].rgbtBlue;
                        totalGreen += imageCopy[i + k][j - l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else if (i == height - 1 && j == 0)
            {
                // bottom left corner
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        totalRed += imageCopy[i - k][j + l].rgbtRed;
                        totalBlue += imageCopy[i - k][j + l].rgbtBlue;
                        totalGreen += imageCopy[i - k][j + l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else if (i == height - 1 && j == width - 1)
            {
                // bottom right corner
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        totalRed += imageCopy[i - k][j - l].rgbtRed;
                        totalBlue += imageCopy[i - k][j - l].rgbtBlue;
                        totalGreen += imageCopy[i - k][j - l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else if (i == 0 && j != 0)
            {
                // top bar (not corner)
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        totalRed += imageCopy[i + k][j + l].rgbtRed;
                        totalBlue += imageCopy[i + k][j + l].rgbtBlue;
                        totalGreen += imageCopy[i + k][j + l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else if (i == height - 1 && j != 0)
            {
                // bottom bar (not corner)
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        totalRed += imageCopy[i - k][j + l].rgbtRed;
                        totalBlue += imageCopy[i - k][j + l].rgbtBlue;
                        totalGreen += imageCopy[i - k][j + l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else if (i != 0 && j == 0)
            {
                // left bar (not corner)
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        totalRed += imageCopy[i + k][j + l].rgbtRed;
                        totalBlue += imageCopy[i + k][j + l].rgbtBlue;
                        totalGreen += imageCopy[i + k][j + l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else if (i != 0 && j == width - 1)
            {
                // right bar (not corner)
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        totalRed += imageCopy[i + k][j - l].rgbtRed;
                        totalBlue += imageCopy[i + k][j - l].rgbtBlue;
                        totalGreen += imageCopy[i + k][j - l].rgbtGreen;
                        counter++;
                    }
                }
            }
            else
            {
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        totalRed += imageCopy[i + k][j + l].rgbtRed;
                        totalGreen += imageCopy[i + k][j + l].rgbtGreen;
                        totalBlue += imageCopy[i + k][j + l].rgbtBlue;
                        counter++;
                    }
                }
            }

            image[i][j].rgbtRed = round(totalRed / counter);
            image[i][j].rgbtBlue = round(totalBlue / counter);
            image[i][j].rgbtGreen = round(totalGreen / counter);
        }
    }
    return;
}

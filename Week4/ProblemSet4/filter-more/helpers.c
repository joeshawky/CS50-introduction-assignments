#include "helpers.h"
#include "math.h"
#include <stdbool.h>
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE imageCopy[height][width];

    memcpy(imageCopy, image, sizeof(RGBTRIPLE) * height * width);

    int gxMatrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyMatrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int totalRed;
    int totalBlue;
    int totalGreen;
    int gxRed;
    int gxBlue;
    int gxGreen;
    int gyRed;
    int gyBlue;
    int gyGreen;
    // float counter;
    bool middleBox;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxRed = 0;
            gxBlue = 0;
            gxGreen = 0;
            gyRed = 0;
            gyBlue = 0;
            gyGreen = 0;
            if (i == 0 && j == 0)
            {
                // top left corner
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
                    }
                }
            }
            else if (i == 0 && j == width - 1)
            {
                // top right corner
                for (int k = 0; k <= 1; k++)
                {
                    for (int l = -1; l <= 0; l++)
                    {
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
                    }
                }
            }
            else if (i == height - 1 && j == 0)
            {
                // bottom left corner
                for (int k = -1; k <= 0; k++)
                {
                    for (int l = 0; l <= 1; l++)
                    {
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
                    }
                }
            }
            else if (i == height - 1 && j == width - 1)
            {
                // bottom right corner
                for (int k = -1; k <= 0; k++)
                {
                    for (int l = -1; l <= 0; l++)
                    {
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
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
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
                    }
                }
            }
            else if (i == height - 1 && j != 0)
            {
                // bottom bar (not corner)
                for (int k = -1; k <= 0; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
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
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
                    }
                }
            }
            else if (i != 0 && j == width - 1)
            {
                // right bar (not corner)
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 0; l++)
                    {
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
                    }
                }
            }
            else
            {
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        gxRed += imageCopy[i + k][j + l].rgbtRed * gxMatrix[l + 1][k + 1];
                        gxBlue += imageCopy[i + k][j + l].rgbtBlue * gxMatrix[l + 1][k + 1];
                        gxGreen += imageCopy[i + k][j + l].rgbtGreen * gxMatrix[l + 1][k + 1];

                        gyRed += imageCopy[i + k][j + l].rgbtRed * gyMatrix[l + 1][k + 1];
                        gyBlue += imageCopy[i + k][j + l].rgbtBlue * gyMatrix[l + 1][k + 1];
                        gyGreen += imageCopy[i + k][j + l].rgbtGreen * gyMatrix[l + 1][k + 1];
                    }
                }
            }
            totalRed = round(hypot(gxRed, gyRed));
            totalBlue = round(hypot(gxBlue, gyBlue));
            totalGreen = round(hypot(gxGreen, gyGreen));
            totalRed = totalRed <= 255 ? totalRed : 255;
            totalBlue = totalBlue <= 255 ? totalBlue : 255;
            totalGreen = totalGreen <= 255 ? totalGreen : 255;
            image[i][j].rgbtRed = totalRed;
            image[i][j].rgbtBlue = totalBlue;
            image[i][j].rgbtGreen = totalGreen;
        }
    }
    return;
}

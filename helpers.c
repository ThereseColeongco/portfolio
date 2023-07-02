#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
// rgb values will be all equal (e.g. all 0x00 for black, all 0xff for white)
// to maintain same brightness or darkness as OG image, average red, blue, and green values
// convert that avg to hexadecimal and that's the color value for r, g, and b
// get the average for each pixel in the image and convert that avg to hexadecimal for each pixel in the image
// or do u even have to convert to hexadecimal?? can't you just use the hexadecimal values directly?? no you have to convert to hexadecimal. rgbtBlue, Red, and Green = all decimal values
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("%i\n", image[i][j].rgbtBlue);
            float gray = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
        }
    }
    return;
}

// Convert image to sepia
//
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // how to cap at 255? if result of any of these values is > 255, let that result = 255.
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255 || sepiaGreen > 255 || sepiaBlue > 255)
            {
                sepiaRed = 255;
                sepiaGreen = 255;
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
// pixels on the left side of image should be on the right side of image and vice versa
// height number of rows, width number of columns
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // keep i stable. for each i, iterate through j. that is what this nested for loop does. then,
    // image[0][0] swap w/ image [0][width - 1]
    // image[0][1] swap w/ image[0][width - 2]
    // image[0][2] swap w/ image[0][width - 3]
    // as j++, height--

    for (int i = 0; i < height; i++)
    {
        // for every pixel in a line, swap with the opposite pixel.
        // that means you don't iterate through entire width. just half of width.
        // if you were to iterate through entire width, you'll start undoing the swapping you did halfway through.
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
// for each pixel, look at the pixels immediately surrounding it.
// average the colors of those pixels.
// that average is the color of the
// if image represents the whole picture, then image[0] represents the first row,
// and image[0][0] represents the pixel in the upper-left corner of the image.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // copy image into copy pixel by pixel in nested for loops
    // get pixel colors from copy but change pixel colors in image
    // if corner pixel, only 3 surrounding pixels
        // image[0][0] has image[0][1], image[1][1], image[1][2] surrounding } (one at same i but j++, then i++ and j++, then keep same i and j++ again)
        // image[0][width - 1] has image[0][width - 2], image[1][width - 1], image[1][width - 2] surrounding
        // image[height - 1][0] has image[height - 1][1], image[height - 2][0], image[height - 2][1] surrounding
        // image[height - 1][width - 1] has image[height - 1][width - 2], image[height - 2][width - 1], image[height - 2][width - 2] surrounding
    // if edge but not corner pixel, only 5 surrounding pixels
        // image[height - 1][width - 2] has image[height - 1][w - 1], image[h - 2][w - 1], image[h - 2][w - 2], image[h - 2][w - 3], image[h - 1][w - 3] surrounding
            // as you move left, j - (k--) (or right: j - (k++))
            // as k changes, l stays the same
        // image[height - 2][width - 1] has image[h - 1][w - 1], image[h - 1][w - 2], image[h - 2][w - 2], image[h - 3][w - 1], image[h - 3][w - 2] surrounding
            // as you move up, i - (l++) (or down: i - (l--))
            // as l changes, k stays the same
    // if not edge or corner pixel, 8 surrounding pixels

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w].rgbtRed = image[h][w].rgbtRed;
            copy[h][w].rgbtGreen = image[h][w].rgbtGreen;
            copy[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float sumR, sumG, sumB;
            sumR = sumG = sumB = 0;
            int total = 0;
            for (int k = (h - 1); k <= h; k++)
            {
                for (int l = (w - 1); l <= w; l++)
                {
                    if (k >= 0 && k <= height - 1 && l >= 0 && l <= width - 1)
                    {
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                        total++;
                    }
                }
            }
            image[h][w].rgbtRed = round(sumR / total);
            image[h][w].rgbtGreen = round(sumG / total);
            image[h][w].rgbtBlue = round(sumB / total);
        }
    }
    return;
}

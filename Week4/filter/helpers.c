#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int somPix;
    float somPixSus1 = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            somPix = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            somPixSus1 = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) % 3);

            if (somPixSus1 >= 1.5 )
            {
                image[i][j].rgbtBlue = somPix + 1;
                image[i][j].rgbtGreen = somPix + 1;
                image[i][j].rgbtRed = somPix + 1;
            }
            else
            {
                image[i][j].rgbtBlue = somPix;
                image[i][j].rgbtGreen = somPix;
                image[i][j].rgbtRed = somPix;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int tempBlue;
    int tempGreen;
    int tempRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tempBlue = image[i][j].rgbtBlue;
            tempGreen = image[i][j].rgbtGreen;
            tempRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;

            image[i][width - (j + 1)].rgbtBlue = tempBlue;
            image[i][width - (j + 1)].rgbtGreen = tempGreen;
            image[i][width - (j + 1)].rgbtRed = tempRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    double tempBlue = 0;
    double tempGreen = 0;
    double tempRed = 0;
    int divisor = 0;
    int boucleI;
    int frontiereI;
    int boucleJ;
    int frontiereJ;
    RGBTRIPLE imageTemp[height][width];

    for (int i = 0; i <= height - 1; i++)
    {

            for (int j = 0; j <= width - 1; j++)
            {

                tempBlue = 0;
                tempGreen = 0;
                tempRed = 0;


                if (i > 0 && j > 0 && i < height - 1 & j < width - 1) // toute la photo
                {
                    divisor = 9;
                    boucleI = i - 1;
                    frontiereI = i + 1;
                    boucleJ = j - 1;
                    frontiereJ = j + 1;
                }
                else if (i == 0 && j == 0) // coin haut gauche
                {
                    divisor = 4;
                    boucleI = i;
                    frontiereI = i + 1;
                    boucleJ = j;
                    frontiereJ = j + 1;
                }
                else if (i == 0 && j != 0 && j != width - 1 ) // ligne du haut
                {
                    divisor = 6;
                    boucleI = i;
                    frontiereI = i + 1;
                    boucleJ = j - 1;
                    frontiereJ = j + 1;
                }
                else if (i == 0 && j == width - 1) // coin haut droit
                {
                    divisor = 4;
                    boucleI = i;
                    frontiereI = i + 1;
                    boucleJ = j - 1;
                    frontiereJ = j;
                }
                else if (j == 0 && i != 0 && i != height - 1) // coté gauche
                {
                    divisor = 6;
                    boucleI = i - 1;
                    frontiereI = i + 1;
                    boucleJ = j;
                    frontiereJ = j + 1;
                }
                else if (j == width - 1 && i != 0 && i != height - 1) // coté droit
                {
                    divisor = 6;
                    boucleI = i - 1;
                    frontiereI = i + 1;
                    boucleJ = j - 1;
                    frontiereJ = j;
                }
                else if (i == width - 1 && j == 0 ) //coin bas gauche
                {
                    divisor = 4;
                    boucleI = i - 1;
                    frontiereI = i;
                    boucleJ = j;
                    frontiereJ = j + 1;
                }
                else if ( i == height - 1 && j != 0 && j != width - 1) // ligne du bas
                {
                    divisor = 6;
                    boucleI = i - 1;
                    frontiereI = i;
                    boucleJ = j - 1;
                    frontiereJ = j + 1;
                }
                else if (i == height - 1 && j == width - 1) // coin du bas droit
                {
                    divisor = 4;
                    boucleI = i - 1;
                    frontiereI = i;
                    boucleJ = j - 1;
                    frontiereJ = j;
                }


                for (int p = boucleI ; p <= frontiereI; p++)
                {
                    for (int q = boucleJ; q <= frontiereJ; q++)
                    {
                        tempBlue = image[p][q].rgbtBlue + tempBlue;
                        tempGreen = image[p][q].rgbtGreen + tempGreen;
                        tempRed = image[p][q].rgbtRed + tempRed;
                    }

                }

                imageTemp[i][j].rgbtBlue = round(tempBlue / divisor);
                imageTemp[i][j].rgbtGreen = round(tempGreen / divisor);
                imageTemp[i][j].rgbtRed = round(tempRed / divisor);



            }

    }
    
    for (int z = 0; z < height; z++)
    {
        for (int y = 0; y < width; y++)
        {
                image[z][y].rgbtBlue = imageTemp[z][y].rgbtBlue;
                image[z][y].rgbtGreen = imageTemp[z][y].rgbtGreen;
                image[z][y].rgbtRed = imageTemp[z][y].rgbtRed;
        }
    }



    return;
}

// Detect edges

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gxBlue = 0;
    int gyBlue = 0;
    int gxGreen = 0;
    int gyGreen = 0;
    int gxRed = 0;
    int gyRed = 0;
    int loopI;
    int borderI;
    int loopJ;
    int borderJ;
    double tempBlue = 0;
    double tempGreen = 0;
    double tempRed = 0;
    
    
    //this array should be normal according to my logic
    int arrayX[3][3] = {{1,0,(-1)},{2,0,(-2)},{1,0,(-1)}};
    int arrayY[3][3] = {{1,2,1},{0,0,0},{(-1),(-2),(-1)}};
    

    
    
    RGBTRIPLE imageTemp[height][width];
    
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxBlue = 0;
            gyBlue = 0;
            gxGreen = 0;
            gyGreen = 0;
            gxRed = 0;
            gyRed = 0;
            tempBlue = 0;
            tempGreen = 0;
            tempRed = 0;
            
                /*if (i > 0 && j > 0 && i < height - 1 & j < width - 1) // all the picture
                {
                    loopI = i - 1;
                    borderI = i + 1;
                    loopJ = j - 1;
                    borderJ = j + 1;
                }
                else if (i == 0 && j == 0) // upper left
                {
                    loopI = i;
                    borderI = i + 1;
                    loopJ = j;
                    borderJ = j + 1;
                }
                else if (i == 0 && j != 0 && j != width - 1 ) // upp
                {
                    loopI = i;
                    borderI = i + 1;
                    loopJ = j - 1;
                    borderJ = j + 1;
                }
                else if (i == 0 && j == width - 1) //upper right
                {
                    loopI = i;
                    borderI = i + 1;
                    loopJ = j - 1;
                    borderJ = j;

                }
                else if (j == 0 && i != 0 && i != height - 1) //left side
                {
                    loopI = i - 1;
                    borderI = i + 1;
                    loopJ = j;
                    borderJ = j + 1;

                }
                else if (j == width - 1 && i != 0 && i != height - 1) //right side
                {
                    
                    loopI = i - 1;
                    borderI = i + 1;
                    loopJ = j - 1;
                    borderJ = j;

                }
                else if (i == height - 1 && j == 0 ) //lower left
                {
                    loopI = i - 1;
                    borderI = i;
                    loopJ = j;
                    borderJ = j + 1;
                    
 
                }
                else if ( i == height - 1 && j != 0 && j != width - 1) // low
                {
                    loopI = i - 1;
                    borderI = i;
                    loopJ = j - 1;
                    borderJ = j + 1;

                }
                else if (i == height - 1 && j == width - 1) // lower right
                {
                    loopI = i - 1;
                    borderI = i;
                    loopJ = j - 1;
                    borderJ = j;
 
                }*/


                for (int p = i - 1 ; p <= i + 1; p++)
                {
                    for (int q = j - 1; q <= j + 1; q++)
                    {
                        if (p < 0 || p > height - 1 || q < 0 || q > width - 1)
                    {
                        continue;
                    }
                        
                        gxBlue = image[p][q].rgbtBlue*arrayX[i + 1 - (p)][j + 1 - (q)] + gxBlue;
                        gyBlue = image[p][q].rgbtBlue*arrayY[i + 1 - (p)][j + 1 - (q)] + gyBlue;
                        gxGreen = image[p][q].rgbtGreen*arrayX[i + 1 - (p)][j + 1 - (q)] + gxGreen;
                        gyGreen = image[p][q].rgbtGreen*arrayY[i + 1 - (p)][j + 1 - (q)] + gyGreen;
                        gxRed = image[p][q].rgbtRed*arrayX[i + 1 - (p)][j + 1 - (q)] + gxRed;
                        gyRed = image[p][q].rgbtRed*arrayY[i + 1 - (p)][j + 1 - (q)] + gyRed;
                        
                    }

                }

                tempBlue = sqrt(pow(gxBlue, 2) + pow(gyBlue, 2));
                tempGreen = sqrt(pow(gxGreen, 2) + pow(gyGreen, 2));
                tempRed = sqrt(pow(gxRed, 2) + pow(gyRed, 2));

                
                if (tempBlue >= 255)
                {
                    imageTemp[i][j].rgbtBlue = 255;
                } else
                {
                    imageTemp[i][j].rgbtBlue = round(tempBlue);
                }
                
                if (tempGreen >= 255)
                {
                    imageTemp[i][j].rgbtGreen = 255;
                } else
                {
                    imageTemp[i][j].rgbtGreen = round(tempGreen);
                }
                
                if (tempRed >= 255)
                {
                    imageTemp[i][j].rgbtRed = 255;
                } else
                {
                    imageTemp[i][j].rgbtRed = round(tempRed);
                }
                
                

            }

    }
    
    for (int z = 0; z < height; z++)
    {
        for (int y = 0; y < width; y++)
        {
                image[z][y].rgbtBlue = imageTemp[z][y].rgbtBlue;
                image[z][y].rgbtGreen = imageTemp[z][y].rgbtGreen;
                image[z][y].rgbtRed = imageTemp[z][y].rgbtRed;
        }
    }
            
            
    return;
}

/*if (i > 0 && j > 0 && i < height - 1 & j < width - 1) // toute la photo
                {
                   gxBlue = (- 1)*image[i - 1][j - 1].rgbtBlue + (- 2)*image[i][j - 1].rgbtBlue + (- 1)*image[i + 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                   gyBlue = (- 1)*image[i - 1][j - 1].rgbtBlue + (- 2)*image[i - 1][j].rgbtBlue + (- 1)*image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            
                   gxGreen = (- 1)*image[i - 1][j - 1].rgbtGreen + (- 2)*image[i][j - 1].rgbtGreen + (- 1)*image[i + 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                   gyGreen = (- 1)*image[i - 1][j - 1].rgbtGreen + (- 2)*image[i - 1][j].rgbtGreen + (- 1)*image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            
                   gxRed = (- 1)*image[i - 1][j - 1].rgbtRed + (- 2)*image[i][j - 1].rgbtRed + (- 1)*image[i + 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + 2*image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                   gyRed = (- 1)*image[i - 1][j - 1].rgbtRed + (- 2)*image[i - 1][j].rgbtRed + (- 1)*image[i - 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + 2*image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
             
                }
                else if (i == 0 && j == 0) // coin haut gauche
                {
                   gxBlue = 2*image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                   gyBlue = -1*image[i - 1][j - 1].rgbtBlue -2*image[i - 1][j].rgbtBlue -1*image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            
                   gxGreen = 2*image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                   gyGreen = 2*image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            
                   gxRed = 2*image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                   gyRed = 2*image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed; 
                }
                else if (i == 0 && j != 0 && j != width - 1 ) // ligne du haut
                {
                   gxBlue = -2*image[i][j - 1].rgbtBlue -1*image[i + 1][j - 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                   gyBlue = image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            
                   gxGreen = -2*image[i][j - 1].rgbtGreen -1*image[i + 1][j - 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                   gyGreen = image[i + 1][j - 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            
                   gxRed = -2*image[i][j - 1].rgbtRed -1*image[i + 1][j - 1].rgbtRed + 2*image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                   gyRed = image[i + 1][j - 1].rgbtRed + 2*image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                }
                else if (i == 0 && j == width - 1) // coin haut droit
                {
                   gxBlue = -2*image[i][j - 1].rgbtBlue -1*image[i + 1][j - 1].rgbtBlue;
                   gyBlue = image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue;
            
                   gxGreen = -2*image[i][j - 1].rgbtGreen -1*image[i + 1][j - 1].rgbtGreen;
                   gyGreen = image[i + 1][j - 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen;
            
                   gxRed = -2*image[i][j - 1].rgbtRed -1*image[i + 1][j - 1].rgbtRed;
                   gyRed = image[i + 1][j - 1].rgbtRed + 2*image[i + 1][j].rgbtRed;
                }
                else if (j == 0 && i != 0 && i != height - 1) // coté gauche
                {
                   gxBlue = image[i - 1][j + 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                   gyBlue = -2*image[i - 1][j].rgbtBlue -1*image[i - 1][j + 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            
                   gxGreen = image[i - 1][j + 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                   gyGreen = -2*image[i - 1][j].rgbtGreen -1*image[i - 1][j + 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            
                   gxRed = image[i - 1][j + 1].rgbtRed + 2*image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                   gyRed = -2*image[i - 1][j].rgbtRed -1*image[i - 1][j + 1].rgbtRed + 2*image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                }
                else if (j == width - 1 && i != 0 && i != height - 1) // coté droit
                {
                   gxBlue = -1 * image[i - 1][j - 1].rgbtBlue -2*image[i][j - 1].rgbtBlue -1*image[i + 1][j - 1].rgbtBlue;
                   gyBlue = -1*image[i - 1][j - 1].rgbtBlue -2*image[i - 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue;
            
                   gxGreen = -1 * image[i - 1][j - 1].rgbtGreen -2*image[i][j - 1].rgbtGreen -1*image[i + 1][j - 1].rgbtGreen;
                   gyGreen = -1*image[i - 1][j - 1].rgbtGreen -2*image[i - 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen;
            
                   gxRed = -1 * image[i - 1][j - 1].rgbtRed -2*image[i][j - 1].rgbtRed -1*image[i + 1][j - 1].rgbtRed;
                   gyRed = -1*image[i - 1][j - 1].rgbtRed -2*image[i - 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + 2*image[i + 1][j].rgbtRed;
                }
                else if (i == width - 1 && j == 0 ) //coin bas gauche
                {
                   gxBlue = image[i - 1][j + 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue;
                   gyBlue = -2*image[i - 1][j].rgbtBlue -1*image[i - 1][j + 1].rgbtBlue;
            
                   gxGreen = image[i - 1][j + 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen;
                   gyGreen = -2*image[i - 1][j].rgbtGreen -1*image[i - 1][j + 1].rgbtGreen;
            
                   gxRed = image[i - 1][j + 1].rgbtRed + 2*image[i][j + 1].rgbtRed;
                   gyRed = -2*image[i - 1][j].rgbtRed -1*image[i - 1][j + 1].rgbtRed;
                }
                else if ( i == height - 1 && j != 0 && j != width - 1) // ligne du bas
                {
                   gxBlue = -1 * image[i - 1][j - 1].rgbtBlue -2*image[i][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue;
                   gyBlue = -1*image[i - 1][j - 1].rgbtBlue -2*image[i - 1][j].rgbtBlue -1*image[i - 1][j + 1].rgbtBlue;
            
                   gxGreen = -1 * image[i - 1][j - 1].rgbtGreen -2*image[i][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen;
                   gyGreen = -1*image[i - 1][j - 1].rgbtGreen -2*image[i - 1][j].rgbtGreen -1*image[i - 1][j + 1].rgbtGreen;
            
                   gxRed = -1 * image[i - 1][j - 1].rgbtRed -2*image[i][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + 2*image[i][j + 1].rgbtRed;
                   gyRed = -1*image[i - 1][j - 1].rgbtRed -2*image[i - 1][j].rgbtRed -1*image[i - 1][j + 1].rgbtRed;
                }
                else if (i == height - 1 && j == width - 1) // coin du bas droit
                {
                   gxBlue = -1*image[i - 1][j - 1].rgbtBlue -2*image[i][j - 1].rgbtBlue;
                   gyBlue = -1*image[i - 1][j - 1].rgbtBlue -2*image[i - 1][j].rgbtBlue;
            
                   gxGreen = -1*image[i - 1][j - 1].rgbtGreen -2*image[i][j - 1].rgbtGreen;
                   gyGreen = -1*image[i - 1][j - 1].rgbtGreen -2*image[i - 1][j].rgbtGreen;
            
                   gxRed = -1 * image[i - 1][j - 1].rgbtRed -2*image[i][j - 1].rgbtRed;
                   gyRed = -1*image[i - 1][j - 1].rgbtRed -2*image[i - 1][j].rgbtRed;
                }
            
            
            
            imageTemp[i][j].rgbtBlue = sqrt(pow(gxBlue, 2)+ pow(gyBlue, 2));
            imageTemp[i][j].rgbtGreen = sqrt(pow(gxGreen, 2) + pow(gyGreen, 2));
            imageTemp[i][j].rgbtRed = sqrt(pow(gxRed, 2) + pow(gyRed, 2));
            
            if (imageTemp[i][j].rgbtBlue > 255)
            {
                imageTemp[i][j].rgbtBlue = 255;
            }
            
            if (imageTemp[i][j].rgbtGreen > 255)
            {
                imageTemp[i][j].rgbtGreen = 255;
            }
            
            if (imageTemp[i][j].rgbtRed > 255)
            {
                imageTemp[i][j].rgbtRed = 255;
            }
            
        }
    }
    
    for (int z = 0; z < height; z++)
    {
        for (int y = 0; y < width; y++)
        {
                image[z][y].rgbtBlue = imageTemp[z][y].rgbtBlue;
                image[z][y].rgbtGreen = imageTemp[z][y].rgbtGreen;
                image[z][y].rgbtRed = imageTemp[z][y].rgbtRed;
        }
    }*/

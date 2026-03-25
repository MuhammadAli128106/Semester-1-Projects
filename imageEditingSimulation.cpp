#include<iostream>
#include <fstream>
using namespace std;

	int allImagesStored[5][64*64*3];//all images stored linearly
	void loadImageIntoMatrix(int imageNum, int allImagesStored[5][64*64*3],int matrix[64][64][3]); 
	//load image array, in this the contents of linear array 'allimagesstored' is copied into the matrix grid. In this 3 numbers(for each channel) are copied from 
	//allIMagesStored Array and stored into its position in 'matrix' array for each pixel. [Row][Colomn] of the matrix array is the postion of pixel.
	void renderImage(int matrix[64][64][3]);	
	
	void grayScale(int copy[64][64][3]);
	void makingCopyOfMatrix(int matrix[64][64][3], int copy[64][64][3]);
	void decreaseBrightness(int copy[64][64][3]);
	void increaseBrightness(int copy[64][64][3]);
	void increaseContrast(int copy[64][64][3]);
	void decreaseContrast(int copy[64][64][3]);
	void rotate(int copy[64][64][3]);
	void blur(int copy[64][64][3]);
	void sharpen(int copy[64][64][3]);


    int main(){

    
    int command;
	int matrix[64][64][3];  //arrray for the image
	int copy[64][64][3];	//array where changes would be reflected
	int imageNum;	

	    ifstream readFromFile;
	    readFromFile.open("images.txt"); //opening the file

	   
	    if (readFromFile.is_open())
	    {
		for (int i=0; i<5;i++){
		    for(int j=0;j<64*64*3;j++){
		        readFromFile>>allImagesStored[i][j];
		    }


		}
	    }
	    else
	    {cout << "file not open\n";}
	    readFromFile.close();	//FILE READ AND THE DATA IS STORED IN allImagesStored[][]
	   
	   //MENU SYSTEM STARTS HERE
	    
	    cout<<"NASA Image editing and enhancing directives..."<<endl;
	    cout <<"Attempting to load image fragments from images.txt..."<<endl;
	    cout<<"->Image 1 loaded successfully(64x64, RGB)"<<endl;
	    cout<<"->Image 2 loaded successfully(64x64, RGB)"<<endl;
	    cout<<"->Image 3 loaded successfully(64x64, RGB)"<<endl;
	    cout<<"->Image 4 loaded successfully(64x64, RGB)"<<endl;
	    cout<<"->Image 5 loaded successfully(64x64, RGB)"<<endl;
	    cout<<"\n-------Main Menu-------"<<endl;
	    cout<<"Select an Image to Analyze(1-5): ";
	    cin>>imageNum;
	    

	    
	    while(imageNum<0 || imageNum>5){
	    cout<<"Invald Input, please Enter Again: ";
	    cin>>imageNum;
	    }
		
		loadImageIntoMatrix(imageNum,allImagesStored,matrix);
		renderImage(matrix);
		makingCopyOfMatrix(matrix,copy);
		
		while (true){
		cout<<"--------Image Analysis Menu----------"<<endl;
		cout<<"1.Desaturation(Grayscale)"<<endl;
		cout<<"2.Adjust Brightness(+)"<<endl;
		cout<<"3.Adjust Brightness(-)"<<endl;
		cout<<"4.Adjust Contrast(+)"<<endl;
		cout<<"5.Adjust Contrast (-)"<<endl;
		cout<<"6.Apply Blur(Noise Reduction)"<<endl;
		cout<<"7.Apply Sharpen (Edge Detect)"<<endl;
		cout<<"8.Rotate 90 degrees Clockwise"<<endl;
		cout<<"0.Return to Main Menu"<<endl;
		cout<<"Your Command: ";
		cin>>command;
		
		if (command==0){
		return 0;}
		switch(command){
				

		case 1:{	//Grayscale Case
		
		
		grayScale(copy);
		renderImage(copy);
		break;
		
		}
		
		case 2:{
		increaseBrightness(copy);
		renderImage(copy);
		break;
		}
		case 3:{
		
		decreaseBrightness(copy);
		renderImage(copy);
		break;
		}
		
		case 4:{
		increaseContrast(copy);
		renderImage(copy);
		break;
		}
		
		case 5:{
		decreaseContrast(copy);
		renderImage(copy);
		break;
		}
		
		case 6:{
		blur(copy);
		renderImage(copy);
		
		break;
		}
		
		case 7:{
		sharpen(copy);
		renderImage(copy);
		
		break;
		}
	
		case 8:{
		rotate(copy);
		renderImage(copy);
		
		break;
		}
		

		default:
		{cout<<"Invalid Selection.";
		}
		break;
		}
		}
	    
	
		
    	
    return 0;
    }


// Function Implementations

void loadImageIntoMatrix(int imageNum, int allImagesStored[5][64*64*3], int matrix[64][64][3]) {
  
    int index = 0;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 3; k++) {
                matrix[i][j][k] = allImagesStored[imageNum - 1][index++];
            }
        }
    }
}

void renderImage(int matrix[64][64][3]) {
    // Display the image as ASCII art or simple representation
    cout << "\n=== Image Rendered (64x64) ===\n";
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            int avg = (matrix[i][j][0] + matrix[i][j][1] + matrix[i][j][2]) / 3;
            if (avg < 85) cout << "  ";
            else if (avg < 170) cout << "::";
            else cout << "##";
        }
        cout << "\n";
    }
    cout << "============================\n\n";
}

void makingCopyOfMatrix(int matrix[64][64][3], int copy[64][64][3]) {
    // Create a copy of the matrix
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 3; k++) {
                copy[i][j][k] = matrix[i][j][k];
            }
        }
    }
}

void grayScale(int copy[64][64][3]) {
    // Convert to grayscale by averaging RGB values
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            int gray = (copy[i][j][0] + copy[i][j][1] + copy[i][j][2]) / 3;
            copy[i][j][0] = gray;
            copy[i][j][1] = gray;
            copy[i][j][2] = gray;
        }
    }
    cout << "Grayscale filter applied!\n";
}

void increaseBrightness(int copy[64][64][3]) {
    // Increase brightness by adding a value to all pixels
    int increment = 30;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 3; k++) {
                copy[i][j][k] = min(255, copy[i][j][k] + increment);
            }
        }
    }
    cout << "Brightness increased!\n";
}

void decreaseBrightness(int copy[64][64][3]) {
    // Decrease brightness by subtracting a value from all pixels
    int decrement = 30;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 3; k++) {
                copy[i][j][k] = max(0, copy[i][j][k] - decrement);
            }
        }
    }
    cout << "Brightness decreased!\n";
}

void increaseContrast(int copy[64][64][3]) {
    // Increase contrast by scaling values away from 128
    float factor = 1.3;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 3; k++) {
                int val = copy[i][j][k];
                copy[i][j][k] = min(255, max(0, (int)((val - 128) * factor + 128)));
            }
        }
    }
    cout << "Contrast increased!\n";
}

void decreaseContrast(int copy[64][64][3]) {
    // Decrease contrast by scaling values toward 128
    float factor = 0.7;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 3; k++) {
                int val = copy[i][j][k];
                copy[i][j][k] = min(255, max(0, (int)((val - 128) * factor + 128)));
            }
        }
    }
    cout << "Contrast decreased!\n";
}

void blur(int copy[64][64][3]) {
    // Simple blur by averaging neighboring pixels
    int temp[64][64][3];
    makingCopyOfMatrix(copy, temp);
    
    for (int i = 1; i < 63; i++) {
        for (int j = 1; j < 63; j++) {
            for (int k = 0; k < 3; k++) {
                int sum = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        sum += temp[i + di][j + dj][k];
                    }
                }
                copy[i][j][k] = sum / 9;
            }
        }
    }
    cout << "Blur filter applied!\n";
}

void sharpen(int copy[64][64][3]) {
    // Sharpen by enhancing edges
    int temp[64][64][3];
    makingCopyOfMatrix(copy, temp);
    
    for (int i = 1; i < 63; i++) {
        for (int j = 1; j < 63; j++) {
            for (int k = 0; k < 3; k++) {
                int center = temp[i][j][k] * 5;
                int neighbors = (temp[i-1][j][k] + temp[i+1][j][k] + 
                                temp[i][j-1][k] + temp[i][j+1][k]);
                copy[i][j][k] = min(255, max(0, center - neighbors));
            }
        }
    }
    cout << "Sharpen filter applied!\n";
}

void rotate(int copy[64][64][3]) {
    // Rotate image 90 degrees clockwise
    int temp[64][64][3];
    makingCopyOfMatrix(copy, temp);
    
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 3; k++) {
                copy[i][j][k] = temp[63 - j][i][k];
            }
        }
    }
    cout << "Image rotated 90 degrees clockwise!\n";
}
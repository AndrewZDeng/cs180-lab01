#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"

#include "triangle.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int main(int argc, char **argv)
{
	if(argc != 19) {
		cout << "Usage: Lab1 <out_image_name>.png width height \\" << endl;
		cout << "\t x1 y1 r1 g1 b1 \\" << endl;
		cout << "\t x2 y2 r2 g2 b2 \\" << endl;
		cout << "\t x3 y3 r3 g3 b3" << endl;
		return 0;
	}
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);
	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
	
	int verts[3][2];
	unsigned char colors[3][3];
	verts[0][0] = atoi( argv[4] ); verts[0][1] = atoi( argv[5] );
	colors[0][0] = atoi( argv[6] ); colors[0][1] = atoi( argv[7] ); colors[0][2] = atoi( argv[8] );
	
	verts[1][0] = atoi( argv[9] ); verts[1][1] = atoi( argv[10] );
	colors[1][0] = atoi( argv[11] ); colors[1][1] = atoi( argv[12] ); colors[1][2] = atoi( argv[13] );
	
	verts[2][0] = atoi( argv[14] ); verts[2][1] = atoi( argv[15] );
	colors[2][0] = atoi( argv[16] ); colors[2][1] = atoi( argv[17] ); colors[2][2] = atoi( argv[18] );
	
	
	Triangle triangle( verts );
	
	int numInnerPts = triangle.getNumInnerPts();
	vector<int> innerPoints = triangle.getInnerPoints();
	vector<double> baryCoeffs = triangle.getBaryCoeffs();
	
	for( int i=0; i < numInnerPts; i++ ) {
		unsigned char r = baryCoeffs[i*3]*(double)colors[0][0] + baryCoeffs[i*3+1]*(double)colors[1][0] + baryCoeffs[i*3+2]*(double)colors[2][0];
		unsigned char g = baryCoeffs[i*3]*(double)colors[0][1] + baryCoeffs[i*3+1]*(double)colors[1][1] + baryCoeffs[i*3+2]*(double)colors[2][1];
		unsigned char b = baryCoeffs[i*3]*(double)colors[0][2] + baryCoeffs[i*3+1]*(double)colors[1][2] + baryCoeffs[i*3+2]*(double)colors[2][2];
		image->setPixel(innerPoints[i*2], innerPoints[i*2 + 1], r, g, b);
	}
	
	// Draw a rectangle
	/*
	for(int y = 10; y < 20; ++y) {
		for(int x = 20; x < 40; ++x) {
			unsigned char r = 255;
			unsigned char g = 0;
			unsigned char b = 0;
			image->setPixel(x, y, r, g, b);
		}
	}
	*/
	
	// Write image to file
	image->writeToFile(filename);
	return 0;
}

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <climits>

class Triangle {
	
	public:
		Triangle( int verts[][2] );
		~Triangle();
		void setVertex( int verts[][2] );
		int getNumInnerPts();
		std::vector<int> getInnerPoints();
		std::vector<double> getBaryCoeffs();
	
	
	private:
		int verts[3][2];
		int xmin, ymin, xmax, ymax;
		double area;
		int numInnerPts;
		std::vector<int> innerPoints;
		std::vector<double> baryCoeffs;
	
		void coeffsCalc();
		
	
};

double det2d( double Mat[][2] ) {
	
	return Mat[0][0]*Mat[1][1] - Mat[0][1]*Mat[1][0];
	
}

Triangle::Triangle( int verts[][2] ) {
	
	setVertex( verts );
	
}

Triangle::~Triangle() {
	innerPoints.clear();
	baryCoeffs.clear();
}

void Triangle::setVertex( int verts[][2] ) {
	
	xmin = ymin = INT_MAX;
	xmax = ymax = INT_MIN;
	for( int i=0; i < 3; i++ ) {
		this->verts[i][0] = verts[i][0];
		if( verts[i][0] < xmin ) xmin = verts[i][0];
		if( verts[i][0] > xmax ) xmax = verts[i][0];
		this->verts[i][1] = verts[i][1];
		if( verts[i][1] < ymin ) ymin = verts[i][1];
		if( verts[i][1] > ymax ) ymax = verts[i][1];
	}
	
	double Mat[2][2];
	Mat[0][0] = verts[1][0] - verts[0][0];
	Mat[1][0] = verts[1][1] - verts[0][1];
	Mat[0][1] = verts[2][0] - verts[0][0];
	Mat[1][1] = verts[2][1] - verts[0][1];
	
	area = det2d( Mat );
	
	coeffsCalc();
	
}

void Triangle::coeffsCalc() {
	
	numInnerPts = 0;
	innerPoints.clear();
	baryCoeffs.clear();
	
	double Mat[2][2];
	for( int x=xmin; x <= xmax; x++ ) {
		for( int y=ymin; y <= ymax; y++ ) {
			Mat[0][0] = verts[0][0] - verts[2][0];
			Mat[1][0] = verts[0][1] - verts[2][1];
			Mat[0][1] = x - verts[2][0];
			Mat[1][1] = y - verts[2][1];
			
			double beta = det2d( Mat ) / area;
			
			Mat[0][0] = verts[1][0] - verts[0][0];
			Mat[1][0] = verts[1][1] - verts[0][1];
			Mat[0][1] = x - verts[0][0];
			Mat[1][1] = y - verts[0][1];
			
			double gamma = det2d( Mat ) / area;
			double alpha = 1 - beta - gamma;
			
			if( 0 <= alpha && alpha <= 1 &&
			    0 <= beta && beta <= 1 &&
			    0 <= gamma && gamma <= 1 ) {
				
				numInnerPts++;
				innerPoints.push_back( x );
				innerPoints.push_back( y );
				
				baryCoeffs.push_back( alpha );
				baryCoeffs.push_back( beta );
				baryCoeffs.push_back( gamma );
				
			}
		} // y
	} // x
	
}

int Triangle::getNumInnerPts() {
	return numInnerPts;
}

std::vector<int> Triangle::getInnerPoints() {
	return innerPoints;
}

std::vector<double> Triangle::getBaryCoeffs() {
	return baryCoeffs;
}


#endif
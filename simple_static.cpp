#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>

#include <boost/progress.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
namespace btime = boost::posix_time;
// Use progress_timer ?

#define EIGEN_NO_AUTOMATIC_RESIZING
#define EIGEN_NO_MALLOC

#include <Eigen/Eigen>
#include "EigenQPStatic.hpp"

using namespace Eigen;
using namespace std;

int main()
{
	#define n 2 // Variables
	#define p 0 // Equality Constraints
	#define m 3 // Inequality Constraints
		
	cout << setprecision(10);
	int count = 10000;
	
	// Add n rows to constraints for x >= 0
	EMATd(n, n) H;
	EMATd(n + m, n) A;
	EMATd(p, n) Ae;
	EVECd(n) x, f;
	EVECd(m + n) b;
	EVECd(p) be;
	
	be.setZero(p);
	
	H = EMATd(n, n)::Identity();
	//f = EVECd(::Zero(n);
	A <<
		-EMATd(n, n)::Identity(),
		-1, -2,
		-1, 1,
		1, 0;
	b <<
		EVECd(n)::Zero(),
		-2, 1, 3; //, ;
	
	// Convert from A x <= b  ==>  -A^T >= b
	/*
	A.transposeInPlace();
	A *= -1;
	Ae.transposeInPlace();
	Ae *= -1;
	*/
	
	btime::ptime tic = btime::microsec_clock::local_time();
	//boost::timer timer;
	// Does this modify H?
	double objVal;
	for (int i = 0; i < count; ++i)
	{
		objVal = QP::solve_quadprog<n, p, m + n>(H, f, -Ae.transpose(), be, -A.transpose(), b, x);
	}
	btime::time_duration toc = btime::microsec_clock::local_time() - tic;
	cout << "Elapsed time: " << setprecision(8) << toc.total_milliseconds() << " ms\n";
	cout << "obj: " << objVal << "\nx: " << x << "\n\n";
	return 0; 
}

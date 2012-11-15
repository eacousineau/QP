#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>
#include "uQuadProg++.hh"

#include <boost/progress.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
namespace btime = boost::posix_time;
// Use progress_timer ?

#include <Eigen/Eigen>
#include "EigenQP.h"

using namespace Eigen;
using namespace std;

int main()
{
	int n = 2, // Variables
		p = 0, // Equality Constraints
		m = 3; // Inequality Constraints
		
	cout << setprecision(10);
	int count = 10000;
	
	// Add n rows to constraints for x >= 0
	MatrixXd H(n, n), A(m + n, n), Ae(p, n);
	VectorXd x(n), f(n), b(m + n);
	VectorXd be(p);
	
	H = MatrixXd::Identity(n, n);
	f = VectorXd::Zero(n);
	A <<
		-MatrixXd::Identity(n, n),
		-1, -2,
		-1, 1,
		1, 0;
	b <<
		VectorXd::Zero(n),
		-2, 1, 3; //, ;
	
	// For their library
	A.transposeInPlace();
	Ae.transposeInPlace();
	
	btime::ptime tic = btime::microsec_clock::local_time();
	//boost::timer timer;
	// Does this modify H?
	double objVal;
	for (int i = 0; i < count; ++i)
	{
		objVal = QP::solve_quadprog(H, f, -Ae, be, -A, b, x);
	}
	btime::time_duration toc = btime::microsec_clock::local_time() - tic;
	cout << "Elapsed time: " << setprecision(8) << toc.total_milliseconds() << " ms\n";
	cout << "obj: " << objVal << "\nx: " << x << "\n\n";
	return 0; 
}

#pragma once
#include <vector>
#include <iostream>


namespace task {

using std::vector;
using std::ostream;
using std::istream;

ostream& operator << (ostream& ostr , const vector<double>& a){
	for (size_t i = 0; i< a.size(); ++i) {
		ostr << a[i] << " ";
	}
	ostr << std::endl;
	return ostr;
}


istream& operator >> (istream& input , vector<double>& a){
	size_t n;
	input >> n;
	if (n == 0) {
		a.clear();
		return input;
	}
	double d;
	for (size_t i =0; i<n; ++ i) {
		input >> d;
		a[i] = d;
	}
	return input;
}


vector <double> operator+ (const vector<double>& a, const vector<double>& b){
    vector<double> c;
    for (size_t i = 0; i < a.size(); ++i)
        c.push_back(a[i] + b[i]);
    return c;
}


vector <double> operator+ (const vector<double>& a){
    vector<double> c;
    for (size_t i = 0; i < a.size(); ++i)
        c.push_back(+a[i]);
    return c;
}


vector <double> operator- (const vector<double>& a, const vector<double>& b){
    vector<double> c;
    for (size_t i = 0; i < a.size(); ++i)
        c.push_back(a[i] - b[i]);
    return c;
}


vector <double> operator- (const vector<double>& a){
    vector<double> c;
    for (size_t i = 0; i < a.size(); ++i)
        c.push_back(-a[i]);
    return c;
}


double operator* (const vector<double>& a, const vector<double>& b){
    double c = 0;
    for (size_t i = 0; i < a.size(); ++i)
        c += a[i]*b[i];
        
    return c;
}


vector<double> operator% (const vector<double>& a, const vector<double>& b){
    vector <double> c;
    c.push_back(a[1]*b[2] - a[2]*b[1]);
    c.push_back(a[2]*b[0] - a[0]*b[2]);
    c.push_back(a[0]*b[1] - a[1]*b[0]);
    return c;
}


bool operator ||(const vector<double>& a, const vector<double>& b){
	
	double mul = a[0]/b[0];
	for (size_t i = 0; i< a.size(); ++i){
		if (b[i]!=0){
			if (a[i] - mul * b[i] > 1e-10 ) return false;
		}
		else if (a[i] != 0 ) return false;
		
	}
	return true;		
}


bool operator &&(const vector<double>& a, const vector<double>& b){
    if (!( a || b)) 
        return false;
    else 
    {
        for (size_t i = 0; i<a.size(); ++i)
            {
                if (b[i]!=0)
                {
                    if (a[i]/b[i] > 0)
                        return true;
                    else return false;
                }
            }
        return false;
    }
}


vector<double> reverse (vector<double>& a){
    double tmp;
    for (size_t i = 0; i < a.size()/2 ;  ++i )
        {
			tmp = a[i];
			a[i] = a[a.size() - 1 - i];
			a[a.size() - 1 - i] = tmp;
        }
    return a;
}


vector<int> operator | (const vector<int>& a, const vector<int>& b){
    vector<int> c;
    for (size_t i = 0; i < a.size() ; ++i ){
        c.push_back( a[i] | b[i] );
    }
    return c;
}


vector<int> operator & (const vector<int>& a, const vector<int>& b){
    vector<int> c;
    for (size_t i = 0; i < a.size() ; ++i ){
        c.push_back( a[i] & b[i] );
    }
    return c;
}

}  // namespace task
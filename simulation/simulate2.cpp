#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

int main()
{
	cout << "Simulating..." << endl;

	int A[ 85 ][ 85 ];

	ifstream input( "matrix.csv" );

	if( !input )
	{
		cout << "Fail to open matrix.csv" << endl;
		input.close();
		exit( 0 );
	}

	for( int i = 0; i < 85; ++i )
	{
		for( int j = 0; j < 85; ++j )
		{
			input >> A[ i ][ j ];
			input.ignore();
		}
	}

	input.close();

	int outDegree[ 85 ];

	for( int j = 0; j < 85; ++j )
	{
		outDegree[ j ] = 0;

		for( int i = 0; i < 85; ++i )
		{
			outDegree[ j ] += A[ i ] [ j ];
		}
	}

	int sum = 0;

	for( int i = 0; i < 85; ++i )
	{
		sum += outDegree[ i ];
	}

	bool alive[ 85 ];
	int total = 0;

	for( int v = 0; v < 85; ++v )
	{
		bool flag = false;

		for( int i = 0; i < 85; ++i )
		{
			if( A[ i ][ v ] > 0 )
			{
				flag = true;
			}
		}
		for( int j = 0; j < 85; ++j )
		{
			if( A[ v ][ j ] > 0 )
			{
				flag = true;
			}
		}

		alive[ v ] = flag;
		total += flag ? 100 : 0;
	}

	double x[ 31 ][ 85 ];

	int cycle = 0;
	while( cycle < 100 )
	{
		bool accesible[ 85 ];
		int bicycle[ 85 ];

		for( int i = 0; i < 85; ++i )
		{
			accesible[ i ] = alive[ i ];
			bicycle[ i ] = alive[ i ] ? 100 : 0;
		}

		int denominator = sum;

		int time = 0;
		while( time < 30 )
		{
			for( int i = 0; i < 85; ++i )
			{
				x[ time ][ i ] = ( x[ time ][ i ] * cycle + bicycle[ i ] * 1.0 / total ) / ( cycle + 1 );
			}

			for( int count = 0; count < total; ++count )
			{
				int rn;

				int start = 0;

				rn = ( ( rand() << 15 ) | rand() ) % denominator;

				while( start < 84 )
				{
					if( accesible[ start ] && rn - outDegree[ start ] < 0 )
					{
						break;
					}

					rn -= outDegree[ start ];
					++start;
				}

				int goal = 0;

				rn = ( ( rand() << 15 ) | rand() ) % outDegree[ start ];

				while( goal < 84 )
				{
					if( rn - A[ start ][ goal ] < 0 )
					{
						break;
					}

					rn -= A[ start ][ goal ];
					++goal;
				}

				if( 1 == bicycle[ start ] )
				{
					accesible[ start ] = false;
					denominator -= outDegree[ start ];
				}
				--bicycle[ start ];

				if( 0 == bicycle[ goal ] )
				{
					accesible[ goal ] = true;
					denominator += outDegree[ goal ];
				}
				++bicycle[ goal ];
			}

			++time;
		}
		for( int i = 0; i < 85; ++i )
		{
			x[ time ][ i ] = ( x[ time ][ i ] * cycle + bicycle[ i ] * 1.0 / total ) / ( cycle + 1 );
		}

		++cycle;

		cout << "Cycle " << cycle << " complete!" << endl;
	}

	ofstream output( "simulation2.csv", std::ios::out );

	if( !output )
	{
		cout << "Fail to open simulation1.csv" << endl;
		output.close();
		exit( 0 );
	}

	for( int i = 0; i < 31; ++i )
	{
		for( int j = 0; j < 84; ++j )
		{
			output << x[ i ][ j ] << ',';
		}

		output << x[ i ][ 84 ] << endl;
	}

	output.close();

	cout << "Complete!" << endl;
}
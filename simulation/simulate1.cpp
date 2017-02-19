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


	double W[ 85 ][ 85 ];

	for( int j = 0; j < 85; ++j )
	{
		int outDegree = 0;

		for( int i = 0; i < 85; ++i )
		{
			outDegree += A[ i ] [ j ];
		}

		if( outDegree > 0 )
		{
			for( int i = 0; i < 85; ++i )
			{
				W[ i ][ j ] = A[ i ][ j ] * 1.0 / outDegree;
			}
		}
		else
		{
			for( int i = 0; i < 85; ++i )
			{
				W[ i ][ j ] = 0;
			}
		}
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
		int bicycle[ 85 ];

		for( int i = 0; i < 85; ++i )
		{
			bicycle[ i ] = alive[ i ] ? 100 : 0;
		}


		int time = 0;
		while( time < 30 )
		{
			for( int i = 0; i < 85; ++i )
			{
				x[ time ][ i ] = ( x[ time ][ i ] * cycle + bicycle[ i ] * 1.0 / total ) / ( cycle + 1 );
			}

			for( int count = 0; count < total; ++count )
			{
				int rn = ( ( rand() << 15 ) | rand() ) % total;

				int start = 0;
				while( start < 84 )
				{
					if( rn - bicycle[ start ] < 0 )
					{
						break;
					}

					rn -= bicycle[ start ];
					++start;
				}

				double rd = ( ( rand() << 15 ) | rand() ) * 1.0 / 0x3FFFFFFF;

				int goal = 0;
				while( goal < 84 )
				{
					if( rd - W[ start ][ goal ] < 0 )
					{
						break;
					}

					rd -= W[ start ][ goal ];
					++goal;
				}

				--bicycle[ start ];
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

	ofstream output( "simulation1.csv", std::ios::out );

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
/************************/
/*	math2.c				*/
/************************/
#include<math.h>
#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include <stdlib.h>

#define	ASIN_DIV 64
#define	ATAN_DIV 64

#define MAX_RND2_TBL	100
int randTbl[MAX_RND2_TBL];


/* ??????? */
double SinTbl[ 360 ] = {

0.000000,0.017452,0.034899,0.052336,0.069756,0.087156,0.104528,0.121869,0.139173,0.156434,
0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292372,0.309017,0.325568,
0.342020,0.358368,0.374607,0.390731,0.406737,0.422618,0.438371,0.453991,0.469472,0.484810,
0.500000,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615662,0.629320,
0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.719340,0.731354,0.743145,0.754710,
0.766044,0.777146,0.788011,0.798635,0.809017,0.819152,0.829038,0.838671,0.848048,0.857167,
0.866025,0.874620,0.882948,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.933580,
0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.974370,0.978148,0.981627,
0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.998630,0.999391,0.999848,
1.000000,0.999848,0.999391,0.998630,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,
0.984808,0.981627,0.978148,0.974370,0.970296,0.965926,0.961262,0.956305,0.951056,0.945519,
0.939693,0.933580,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.874620,
0.866025,0.857167,0.848048,0.838671,0.829037,0.819152,0.809017,0.798635,0.788011,0.777146,
0.766044,0.754710,0.743145,0.731354,0.719340,0.707107,0.694658,0.681998,0.669131,0.656059,
0.642788,0.629320,0.615661,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,
0.500000,0.484810,0.469472,0.453990,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,
0.342020,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,
0.173648,0.156434,0.139173,0.121869,0.104528,0.087156,0.069756,0.052336,0.034900,0.017452,
-0.000000,-0.017452,-0.034900,-0.052336,-0.069757,-0.087156,-0.104528,-0.121869,-0.139173,-0.156434,
-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,
-0.342020,-0.358368,-0.374606,-0.390731,-0.406737,-0.422618,-0.438371,-0.453991,-0.469472,-0.484810,
-0.500000,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.629320,
-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.719340,-0.731354,-0.743145,-0.754710,
-0.766045,-0.777146,-0.788011,-0.798635,-0.809017,-0.819152,-0.829038,-0.838671,-0.848048,-0.857167,
-0.866025,-0.874620,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.933581,
-0.939692,-0.945519,-0.951056,-0.956305,-0.961262,-0.965926,-0.970296,-0.974370,-0.978148,-0.981627,
-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.998630,-0.999391,-0.999848,
-1.000000,-0.999848,-0.999391,-0.998630,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,
-0.984808,-0.981627,-0.978148,-0.974370,-0.970296,-0.965926,-0.961262,-0.956305,-0.951056,-0.945519,
-0.939693,-0.933580,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.874620,
-0.866025,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798635,-0.788011,-0.777146,
-0.766044,-0.754710,-0.743145,-0.731354,-0.719340,-0.707107,-0.694659,-0.681998,-0.669131,-0.656059,
-0.642788,-0.629321,-0.615661,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,
-0.500000,-0.484809,-0.469472,-0.453991,-0.438371,-0.422618,-0.406736,-0.390731,-0.374607,-0.358368,
-0.342020,-0.325568,-0.309017,-0.292372,-0.275638,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,
-0.173648,-0.156434,-0.139173,-0.121869,-0.104528,-0.087156,-0.069757,-0.052336,-0.034900,-0.017452

};

#if 0
double	asin_table1[ ASIN_DIV + 1 ] = {
	0.000000,  0.895283,  1.790785,  2.686724, 
	3.583322,  4.480799,  5.379379,  6.279288, 
	7.180756,  8.084014,  8.989299,  9.896853, 
	10.806923, 11.719760, 12.635625, 13.554784, 
	14.477512, 15.404094, 16.334823, 17.270005, 
	18.209957, 19.155010, 20.105510, 21.061818, 
	22.024313, 22.993394, 23.969482, 24.953021, 
	25.944480, 26.944358, 27.953187, 28.971532, 
	30.000000, 31.039240, 32.089951, 33.152888, 
	34.228866, 35.318773, 36.423574, 37.544325, 
	38.682187, 39.838440, 41.014500, 42.211944, 
	43.432537, 44.678264, 45.951374, 47.254431, 
	48.590378, 49.962627, 51.375167, 52.832715, 
	54.340912, 55.906609, 57.538255, 59.246480, 
	61.044976, 62.951890, 64.992167, 67.201752, 
	69.635865, 72.387561, 75.638489, 79.858207, 
	90.000000
};

double	asin_table2[ ASIN_DIV + 1 ] = {
	71.805128, 71.949032, 72.094054, 72.240221, 
	72.387561, 72.536105, 72.685883, 72.836928, 
	72.989273, 73.142954, 73.298007, 73.454472, 
	73.612389, 73.771799, 73.932748, 74.095283, 
	74.259452, 74.425307, 74.592902, 74.762296, 
	74.933549, 75.106724, 75.281891, 75.459120, 
	75.638489, 75.820077, 76.003973, 76.190268, 
	76.379061, 76.570456, 76.764567, 76.961516, 
	77.161432, 77.364457, 77.570743, 77.780455, 
	77.993773, 78.210893, 78.432029, 78.657415, 
	78.887310, 79.122001, 79.361804, 79.607074, 
	79.858207, 80.115650, 80.379910, 80.651564, 
	80.931279, 81.219822, 81.518097, 81.827168, 
	82.148310, 82.483070, 82.833357, 83.201569, 
	83.590796, 84.005130, 84.450191, 84.934071, 
	85.469191, 86.076460, 86.796651, 87.735038, 
	90.000000
};

double	asin_table3[ ASIN_DIV + 1 ] = {
	84.268032, 84.313027, 84.358379, 84.404097, 
	84.450191, 84.496669, 84.543543, 84.590821, 
	84.638515, 84.686635, 84.735195, 84.784205, 
	84.833678, 84.883629, 84.934071, 84.985019, 
	85.036488, 85.088496, 85.141058, 85.194194, 
	85.247923, 85.302265, 85.357241, 85.412875, 
	85.469191, 85.526213, 85.583971, 85.642492, 
	85.701809, 85.761954, 85.822963, 85.884876, 
	85.947732, 86.011577, 86.076460, 86.142431, 
	86.209549, 86.277876, 86.347478, 86.418431, 
	86.490816, 86.564724, 86.640256, 86.717523, 
	86.796651, 86.877782, 86.961076, 87.046716, 
	87.134913, 87.225909, 87.319991, 87.417496, 
	87.518826, 87.624472, 87.735038, 87.851282, 
	87.974183, 88.105034, 88.245614, 88.398482, 
	88.567568, 88.759486, 88.987131, 89.283798, 
	90.000000
};
#endif

double	atan_table[ ATAN_DIV + 1 ] = {
	0.000000,  0.895174,  1.789911,  2.683775, 
	3.576334,  4.467159,  5.355825,  6.241914, 
	7.125016,  8.004729,  8.880659,  9.752425, 
	10.619655, 11.481991, 12.339087, 13.190611, 
	14.036243, 14.875682, 15.708638, 16.534838, 
	17.354025, 18.165957, 18.970408, 19.767169, 
	20.556045, 21.336859, 22.109448, 22.873665, 
	23.629378, 24.376469, 25.114835, 25.844388, 
	26.565051, 27.276763, 27.979474, 28.673147, 
	29.357754, 30.033280, 30.699723, 31.357085, 
	32.005383, 32.644640, 33.274888, 33.896167, 
	34.508523, 35.112011, 35.706691, 36.292630, 
	36.869898, 37.438572, 37.998732, 38.550465, 
	39.093859, 39.629005, 40.156000, 40.674940, 
	41.185925, 41.689059, 42.184443, 42.672185, 
	43.152390, 43.625165, 44.090620, 44.548862, 
	45.000000
};

/* ?�T���� ? ????? ??? ?*******************************************************/
void AdjustDir( float *dir )
{
	if( *dir >= 360.0 ){
		*dir -= 360.0F;
		AdjustDir(dir);
	}else 
	if ( *dir < 0.0 ){
		*dir += 360.0F;
		AdjustDir(dir);
	}
}

void AdjustDir( int *dir )
{
	if( *dir >= 360 ){
		*dir -= 360;
		AdjustDir(dir);
	}else 
	if ( *dir < 0 ){
		*dir += 360;
		AdjustDir(dir);
	}
}

/* ??????��??????? ***********************************************************/
float SinT( float theat )
{
	float ans;
	
	/* ?�T���� */
	AdjustDir( &theat );
	/* ??????��???? */
	ans = ( float )SinTbl[ (int)theat ];
	
	return ans;
}

/* ??????��??????? ***********************************************************/
float CosT( float theat )
{
	float ans;
	
	ans = SinT( theat + 90.0f );
	
	return ans;
}

/* ????????? *********************************************************************/
float Atan( float x, float y )
{
	int		c = 0;
	float	a;
	float	r = 0;
	float	v, w;
	int		index1, index2;
	float	a1, a2;
	float	ratio;


	if (0.0 == x && 0.0 == y) {
		return 0.0;
	}

	if ( x < 0 ) {
		c += 1;
		v = -x;
	} else {
		v = x;
	}

	if ( y < 0 ) {
		c += 2;
		w = -y;
	} else {
		w = y;
	}

	if ( v < w ) {
		c += 4;
		index1 = ( int )( v / w * ATAN_DIV );
		index2 = index1 + 1;
		ratio = ( v / w * ATAN_DIV ) - ( float ) index1;
	} else {
		index1 =  ( int )( w / v * ATAN_DIV );
		index2 = index1 + 1;
		ratio = ( w / v * ATAN_DIV ) - ( float ) index1;
	}

	if ( index2 > ATAN_DIV ) index2 = ATAN_DIV;
	a1 = ( float )atan_table[ index1 ];
	a2 = ( float )atan_table[ index2 ];
	a = ( 1 - ratio ) * a1 + ratio * a2;

	switch (c) {
	  case 0:
		r = a;
		break;
	  case 1:
		r = 180.0f - a;
		break;
	  case 2:
		r = 360.0f - a;
		break;
	  case 3:
		r = 180.0f + a;
		break;
	  case 4:
		r = 90.0f - a;
		break;
	  case 5:
		r = 90.0f + a;
		break;
	  case 6:
		r = 270.0f + a;
		break;
	  case 7:
		r = 270.0f - a;
		break;
	}

	// StoneAge?
	r -= 135;
	if (r < 0.0) r += 360.0;
	/////////////

	return r;
}

/* ?????�D�� *************************************************************************/
int	Rnd( int min, int max )
{
	int rnd;
	if( ( max + 1 - min ) + min == 0 ) return 0;
	rnd = rand() % ( max + 1 - min ) + min;

	return rnd;
}

void initRand2( void )
{
	int i;
	int j;
	j = (rand() % 100);
	for( i = 0; i < MAX_RND2_TBL; i++ ){
		randTbl[j] = i;
		j++;
		if( j >= MAX_RND2_TBL )
			j = 0;
	}
}

#if 1

int rand2( void )
{
	static int r = 0;
	int ret;

	ret = randTbl[r];
	r++;
	if( r >= MAX_RND2_TBL )
		r = 0;

	return ret;
}

#else

int rand2( void )
{
//	static int r = 0;
	static int under25 = 0;
	static int cnt = 0;
	static int cnt2 = 5;
	int ret;

	ret = (rand() % 100);

//	ret = randTbl[r];
//	r++;
//	if( r >= MAX_RND2_TBL )
//		r = 0;

	if( ret < 25 )
	{
		under25++;
		if( under25 >= 4 && cnt >= cnt2 )
		{
			under25 = 0;
			cnt = 0;
			cnt2++;
			if( cnt2 > 6 )
				cnt2 = 4;
		}
		else
		{
			ret = 99 - ret;
			cnt++;
		}
	}
	else
	{
		if( ret > 85 && cnt > 10 )
		{
			ret = 99 - ret;
			cnt = 0;
			cnt2++;
			if( cnt2 > 6 )
				cnt2 = 4;
		}
		else
		{
			cnt++;
		}
		under25 = 0;
	}

	return ret;
}

#endif


/* ?��???????? *******************************************************************/
float pointLen( float x1, float y1, float x2, float y2 )
{
	float x, y;

	x = x2 - x1;
	y = y2 - y1;

	return (float)sqrt( x*x + y*y );
}

float pointLen2( float x1, float y1, float x2, float y2 )
{
	float x, y;

	x = x2 - x1;
	y = y2 - y1;

	return( x*x + y*y );
}




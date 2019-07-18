#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static double distanceBetweenTwoPoints(double px1, double py1, double px2, double py2)
{
	return sqrt(pow((px2 - px1), 2) + pow((py2 - py1), 2));
}

static double prependicularDistance(double px, double py,
		double vx1, double vy1, double vx2, double vy2)
{
	return fabs((vy2 - vy1) * px - (vx2 - vx1) * py + (vx2 * vy1) - (vy2 * vx1)) /
		sqrt(pow(vy2 - vy1, 2) + pow(vx2 - vx1, 2));
}

static double AngelsOfVectors(double wx1, double wy1, double wx2, double wy2,
			double vx1, double vy1, double vx2, double vy2)
{
	double W = sqrt(pow(wx2 - wx1, 2) + pow(wy2 - wy1, 2));
	double V = sqrt(pow(vx2 - vx1, 2) + pow(vy2 - vy1, 2));
	double temp = ((wx2 - wx1) * (vx2 - vx1) + (wy2 - wy1) * (vy2 - vy1)) / (W * V);
	double teta = acos(temp) * 180.0 / M_PI;
	return fabs(teta);
}

static double hausdorffDistance(double px, double py, double vx1, double vy1, double vx2, double vy2)
{
	if (AngelsOfVectors(vx1, vy1, px, py, vx1, vy1, vx2, vy2) < 90 &&
			AngelsOfVectors(vx2, vy2, px, py, vx2, vy2, vx1, vy1) < 90) {
		return prependicularDistance( px,py,vx1,vy1,vx2,vy2 );
	} else if (AngelsOfVectors(vx1, vy1, px, py, vx1, vy1, vx2, vy2) >= 90) {
		return distanceBetweenTwoPoints( px,py,vx1,vy1 );
	} else if (AngelsOfVectors(vx2, vy2, px, py, vx2, vy2, vx1, vy1) >= 90) {
		return distanceBetweenTwoPoints( px,py,vx2,vy2 );
	}
	return 0;
}

static void Agarwal(double x[], double y[], int n, double epsilon)
{
	int a = 1;
	int i, j, k;
	printf("%lf %lf\n", x[0], y[0]);

	for (i = 0; i < n; i++) {
		a = 1;
		for (j = i + 1; j < n; j++) {
			for (k = i; k < j; k++) {
				if (hausdorffDistance(x[k], y[k], x[i], y[i], x[j], y[j]) >= epsilon) {
					i = j - 1;
					if (i != 0)
						printf("%lf %lf\n", x[i], y[i]);
					a = 0;
					i--;
					break;
				}
			}
			if (!a)
				break;
		}
	}
	printf("%lf %lf\n", x[n - 1], y[n - 1]);
}

static void NewAlgAgarwal(double x[], double y[], int n, double epsilon, double e)
{
	int arr_length1 = 0;
	int i, k;
	double j;
	double *new_x;
	double *new_y;
	for (i = 0; i < n - 1; i++) {
		double temp = x[i];
		while (temp <= x[i + 1]) {
			temp += e;
			arr_length1++;
		}
	}
	new_x = malloc(arr_length1 * sizeof(new_x[0]));
	new_y = malloc(arr_length1 * sizeof(new_y[0]));
	k = 0;
	for (i = 0; i < n - 1; i++) {
		for (j = x[i]; j <= x[i+1]; j += e) {
			new_x[k] = j;
			new_y[k] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) * (j - x[i]) + y[i];
			k++;
		}
	}

	new_x[arr_length1 - 1] = x[n - 1];
	new_y[arr_length1 - 1] = y[n - 1];
	Agarwal(new_x, new_y, arr_length1, epsilon);
}

static void *mextend(void *old, long oldsz, long newsz, int memsz)
{
	void *new = malloc(newsz * memsz);
	memcpy(new, old, oldsz * memsz);
	free(old);
	return new;
}

static void tests(void)
{
	/* Not a good idea to include commented code! */
	//cout << "\n" <<hausdorffDistance(7,3,1,1,5,1) << endl;
	//cout << "\n" <<hausdorffDistance(5,1,1,1,7,3) << endl;
	//cout << "\n" <<hausdorffDistance(4,7,1,5,7,6) << endl;
	//cout << "\n" <<hausdorffDistance(4,6.1,1,5,7,6) << endl;
	//double x[] = {1,5,7};
	//double y[] = {1,1,3};
	//double x[] = {1,4,7,10,15,16,20};
	//double y[] = {5,7,6,10,1,2,3};
	//double x[] = {1,4,7,10,15,16,20};
	//double y[] = {5,6.1,6,10,1,2,3};
	//Agarwal(x,y,7,1);
	//Agarwal(xArr,yArr,cnt,0.02);
	//cout << AngelsOfVectors(5,1,7,3,5,1,1,1) << "\n";
	//cout << AngelsOfVectors(4,1,2,3,4,1,7,1) << "\n";
	//cout << AngelsOfVectors(7,1,10,3,7,1,4,1);
}

int main(void)
{
	FILE *fp = fopen("20081023025304-0.plt", "r");
	int cnt = 0;
	double x, y, t;
	double *X = NULL;
	double *Y = NULL;
	int size = 0;
	if (!fp) {
		fprintf(stderr, "Cannot open file\n");
		return 1;
	}
	while (fscanf(fp, "%lf %lf %lf", &x, &y, &t) == 3) {
		if (cnt == size) {
			size = size ? size * 2 : 512;
			X = mextend(X, cnt, size, sizeof(X[0]));
			Y = mextend(Y, cnt, size, sizeof(Y[0]));
		}
		X[cnt] = x;
		Y[cnt] = x;
		cnt++;
	}
	NewAlgAgarwal(X, Y, cnt, 0.02, 0.3);
	return 0;
}

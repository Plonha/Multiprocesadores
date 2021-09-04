#include <stdio.h>
#include <math.h>
#include <omp.h>

void rk1(int n, char doc[]){
	FILE *fptr;

	fptr=fopen(doc,"w");
	printf("Numero de pasos:%d Atendido por thread:%d\n", n,omp_get_thread_num());
	fprintf(fptr, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
	double h,t,w,ab,k1,k2,k3,k4;
	double w0=M_PI/4,a=0,b=M_PI;
	int i;
	w=w0;
	fprintf(fptr, "%f\t %f\n", a, w);
	for(i=0;i<=n;i++){
		h=(b-a)/n;
		t=a+(h*i);
		ab=t*t;
		k1= h*(t*exp(3*t)-2*w);
		k2= h*((t+h/2.0)*exp(3*(t+h/2.0))-2*(w+k1/2.0));
		k3= h*((t+h/2.0)*exp(3*(t+h/2.0))-2*(w+k2/2.0));
		k4= h*((t+h)*exp(3*(t+h))-2*(w+k3));
		w=w+(1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
		fprintf(fptr, "%f\t %f\n", t, w);
	}
	fclose(fptr);
}

void rk2(int n, char doc[]){
	FILE *fptr;

	fptr=fopen(doc,"w");
	printf("Numero de pasos:%d Atendido por thread:%d\n", n,omp_get_thread_num());
	fprintf(fptr, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
	double h,t,w,ab,k1,k2,k3,k4;
	double w0=M_PI/4,a=0,b=M_PI;
	int i;
	w=w0;
	fprintf(fptr, "%f\t %f\n", a, w);
	for(i=0;i<=n;i++){
		h=(b-a)/n;
		t=a+(h*i);
		ab=t*t;
		k1= h*(1+pow(t-w,2));
		k2= h*(1+pow((t+h/2.0)-(w+k1/2.0),2));
		k3= h*(1+pow((t+h/2.0)-(w+k2/2.0),2));
		k4= h*(1+pow((t+h)-(w+k3),2));
		w=w+(1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
		fprintf(fptr, "%f\t %f\n", t, w);
	}
	fclose(fptr);
}

void rk3(int n, char doc[]){
	FILE *fptr;

	fptr=fopen(doc,"w");
	printf("Numero de pasos:%d Atendido por thread:%d\n", n,omp_get_thread_num());
	fprintf(fptr, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
	double h,t,w,ab,k1,k2,k3,k4;
	double w0=M_PI/4,a=0,b=M_PI;
	int i;
	w=w0;
	fprintf(fptr, "%f\t %f\n", a, w);
	for(i=0;i<=n;i++){
		h=(b-a)/n;
		t=a+(h*i);
		ab=t*t;
		k1= h*(1+w/t);
		k2= h*(1+(w+k1/2.0)/(t+h/2.0));
		k3= h*(1+(w+k2/2.0)/(t+h/2.0));
		k4= h*(1+(w+k3)/(t+h));
		w=w+(1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
		fprintf(fptr, "%f\t %f\n", t, w);
	}
	fclose(fptr);
}


void rk4(int n, char doc[]){
	FILE *fptr;

	fptr=fopen(doc,"w");
	printf("Numero de pasos:%d Atendido por thread:%d\n", n,omp_get_thread_num());
	fprintf(fptr, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
	double h,t,w,ab,k1,k2,k3,k4;
	double w0=M_PI/4,a=0,b=M_PI;
	int i;
	w=w0;
	fprintf(fptr, "%f\t %f\n", a, w);
	for(i=0;i<=n;i++){
		h=(b-a)/n;
		t=a+(h*i);
		ab=t*t;
		k1= h*(cos(2*t*w)+sin(3*t*w));
		k2= h*(cos(2*(t+h/2.0)*(w+k1/2.0))+sin(3*(t+h/2.0)*(w+k1/2.0)));
		k3= h*(cos(2*(t+h/2.0)*(w+k2/2.0))+sin(3*(t+h/2.0)*(w+k2/2.0)));
		k4= h*(cos(2*(t+h)*(w+k3))+sin(3*(t+h)*(w+k3)));
		w=w+(1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
		fprintf(fptr, "%f\t %f\n", t, w);
	}
	fclose(fptr);
}

void main(int argc, char const *argv[])
{
	const double start = omp_get_wtime();
	omp_set_num_threads(4);
	#pragma omp parallel 
	{
		#pragma omp sections
		{
			#pragma omp section
				rk1(50000, "rungek1tlp.txt");
			#pragma omp section
				rk2(50000, "rungek2tlp.txt");
			#pragma omp section
				rk3(50000, "rungek3tlp.txt");
			#pragma omp section
				rk4(50000, "rungek4tlp.txt");
		}
	}
	const double end = omp_get_wtime();
	printf("tomo (%lf) segundos\n", (end - start));
}
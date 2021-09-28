#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    FILE *fptr;
     fptr=fopen("histograma.txt","w");
    image = fopen("poke.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img2_dd.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned int r, g, b;               //Pixel
    unsigned char* ptr;

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));
    int blue[257],green[257], red[257],gris[257];

    for (int i = 0; i < 256; ++i){
    blue[i]=0;
    green[i]=0;
    red[i]=0;
    gris[i]=0;
   }


    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      unsigned char pixel = 0.21*r+0.72*g+0.07*b;
      ptr[cuenta] = pixel; //b
      ptr[cuenta+1] = pixel; //g
      ptr[cuenta+2] = pixel; //r
      cuenta++;

    if(b != -1){
      blue[b]++;
      green[g]++;
      red[r]++;
      gris[pixel]++;}

    }          
             //Grises
    cuenta = ancho;
    for (int i = 0; i < alto*ancho*3; ++i) {
      fputc(ptr[i+(cuenta*3)+2], outputImage);
      fputc(ptr[i+(cuenta*3)+1], outputImage);
      fputc(ptr[i+(cuenta*3)], outputImage);
      cuenta--;
      if (cuenta == 0){
        cuenta = ancho;
      }
    }


  for (int i = 0; i< 256; ++i){
    printf("%d\t%d\t%d\t%d\t%d\n" ,i,blue[i],green[i],red[i],gris[i]);
    fprintf(fptr,"%d\t%d\t%d\t%d\t%d\n" ,i,blue[i],green[i],red[i],gris[i]);
   }

    free(ptr);
    fclose(image);
    fclose(outputImage);
    fclose(fptr);
    return 0;
}

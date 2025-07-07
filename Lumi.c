// Program Lumi - after fjnn - This is a "research" application
// from program fotoj3 based on judi based on old programs Judit, and Jcolor2 (see PhD Judit Lopez-Besora)
// weights parts of bmp picture and finds average partial luminances and deviations, Toni Isalgue and Judit Lopez
// from 13-1-15 DO NOT incorporates camera sensitivity from Judit:  CANON EOS 350 D  (digital camera)
// because it is included automatically in .bmp files
// NOT ACTUAL   modification 20/04/15: computations of DP (DPT, DP1, DP2, DP3) according to Building and Environment 81 (2014) 320-333
// NOT ACTUAL   modification /08/2016 compute histogram of a box and write as data
// modification /08/2016 produce grayscale with luminances
// modification /01/2018 to introduce 3 pictures as hdr
// suggerence 5-8 steps in grey picture for luminances
// modification: Feb 2018 scales of grey modified
// NOT ACTUAL   compiled in lcc, runs in Win32 and Win64, in Linux Ubuntu needs Wine installed
// March 2018: give info for colors, all and parts of picture
// May 2018 incorporates gamma translation from values to luminances in RGB in .jpg/.bmp pictures
// July 2018 improvements on maximum scale value in luminance bar, gamma compression/expansion...
// July 2022, compiles in Dev C++ for windows (iostream.h not needed)
// October 2024  symplified // October 2024, 3 rectangles, and write down averages for the rectangles (R G B, L) and st. deviations. Final plot of Luminances improved
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <io.h>
#include <math.h>
//#include <windows.h>   //not needed
//#include <iostream.h>  //older compiler
int main(void)  {
long Clave1,Clave2,Clave3,Clave9,Rr,Gg,Bb,maxlimit,xini,xefe,yini,yefe;
long long alm,anm,ample,aa,aar,aag,aab,xini1[3],xefe1[3],yini1[3],yefe1[3];
long long i, j, k, n9, ntimexp,interval,ix,iy,ii,ji,ik,jk,ir;
long long xpat,ypat,vpunt,iluminp,escala2,npromirect;
long long altura,anchura,f0alt,x,xl[100],yl[100],limit[20];
double aargb,finterval,rpromirect,rpromirectr,rpromirectg,rpromirectb;
double Lm,falt,fanch,fanch1,falt1,rxl,ryl,r1r,ss,fnlmax,fnlmin,r2,g2,b2,lmax;
double lc2,flc2,factorL,lc2r,lc2g,lc2b,flc2r,flc2g,flc2b;
double ssr,ssg,ssb, rdesvrect,rdesvrecr,rdesvrecg,rdesvrecb,PL,PR,PG,PB;
double rxini,rxefe,ryini,ryefe,rescala2,ri,escalalimit,Vmaxlimit,factor;
double rrEV,su,rnpromirect,R1,G1,B1;
double rluminp,rxpat,rypat,rvpunt,gamm,ugamm,maxcont,timexp,nab,iso,ev,rEV,Clave5c,Clave6;
char c, line[100]; //input: dib1.bmp, dib2.bmp (underexposed), dib3.bmp (overexposed)  //int alt=6000;   MAX  //int anch=9000;
unsigned char b,g,r,bb,gg,rr,bbc,bmax;
FILE *PunteroImagenInicial;
FILE *PunteroImagenInicial1;
FILE *PunteroImagenInicial2;
FILE *PunteroImagenFinal;
FILE *PunteroDatos;
FILE *PunteroClave;
static float Roj[9000][6000],Verd[9000][6000],Azu[9000][6000];
static unsigned char Rojo[9000][6000];
static unsigned char Verde[9000][6000];
static unsigned char Azul[9000][6000];
static unsigned char Rojo1[9000][6000];
static unsigned char Verde1[9000][6000];
static unsigned char Azul1[9000][6000];
static unsigned char Rojo2[9000][6000];
static unsigned char Verde2[9000][6000];
static unsigned char Azul2[9000][6000];
Lm=0.0;
flc2=0.0;
ss=0;
lc2=0;
factorL=0;
rvpunt=0;
rluminp=0;
rxpat=0;
rypat=0;
lc2r=0;
lc2g=0;
lc2b=0;
rxl=0;
ryl=0;
ssr=0;
ssg=0;
ssb=0;
npromirect=0;
rdesvrect=0;
rdesvrecr=0;
rdesvrecg=0;
rdesvrecb=0;
for (i=0; i<100; i++)
        {xl[i]=0;
        yl[i]=0;
};   // end i loop i
;
gamm=2.2; //default value for most cameras
interval=255;
finterval=interval;
printf("Luminance of digital pictures. Needs pictures in non-compressed, s-rgb coded bmp format .bmp as input: \n");
printf(" \n");
printf("Picture files:  dib1.bmp Where ASA/ISO, Exposition, Aperture are given \n");
printf("                dib2.bmp Less exposition, recommended -2 stops \n");
printf("                dib3.bmp More exposition, recommended +2 stops \n");
printf(" \n");
printf("Numerical file (in ascii) input.dat Contents: \n");
printf(" \n");
printf("Line1:   C1, integer, 0 normal processing reads ISO/ASA, Aperture Exposition \n");
printf("Line2:   C2, integer, stops between pictures ('bracketing') \n");
printf("Line3:   C3, integer, number of luminance bands (recommended 5-7) \n");
printf("Line5:   C5c float, value of gamma compression  (if 0, takes 2.2 as default) \n");
printf("Line6:   if C1=0, ISO/ASA  of picture dib1.bmp (example: 200) \n");
printf("Line7:   if C1=0, Aperture of picture dib1.bmp (ex: if f/11, give: 11) \n");
printf("Line8:   if C1=0, Exposition     of   dib1.bmp (ex: if 1/320 s, give: 320) \n");
printf("Line9:   C9 integer ask for RGB values of C9 points (xl[], yl[]). 0 if not \n");
printf("Lines10-11*: xl[], yl[] C9 times 2 numbers (2*C9 files) (*if C9=0 omit) if C9>0 Attention bmp starts left down corner \n");
printf("3 times: \n");
printf("Lin12-13: xini, xefe: x start, x end, x define rectangle to find averages \n");
printf("Lin14-15: yini, yefe, y start, x end, y define rectangle to find averages \n");
printf("          Attention: coordinates from down, left picture \n");
printf("Line24:   Value Normalize cd/m2 Luminance graph (to the right last division) \n");
printf("Line25:   0, normal computation (reserved)\n");
printf("Continue: Intro.   Exit: Ctrl-C \n");
c=getchar();
printf(" \n");
printf("          Results of the script:  \n");
printf(" \n");
printf("res.bmp:  bitmap file, \n");
printf("          picture in grey scale, with bars with the luminance intervals in the lower part (values in the numerical file) \n");
printf(" \n");
printf("Lumi.dat: file with numerical results: \n");
printf(" \n");
printf("          Average and standard deviations in the pictures, luminances, \n");
printf("          Average and standard deviations in the defined rectangles, RGB values and standard deviations, \n");
printf(" \n");
printf("          Luminance values corresponding to each bar on the lower part of the output picture \n");
printf("          First  bar values from 0 and first value in luminance (cd/m2), \n");
printf("          second bar values from first and second, and successively \n");
printf(" \n");
printf("          Values of luminance points indicated (average +/- 1 pixel, total 9) for the 3 pictures and for the central picture only \n");
printf(" \n");
printf("Start:  Intro. Exit: Ctrl-C \n");
c=getchar();
;  //End initializations   
PunteroClave = fopen("input.dat","r");
;  //Read file with codes
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &Clave1);
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &Clave2);
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &Clave3);
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%lf", &Clave5c);
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%lf", &Clave6);
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%lf", &nab);
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%lf", &timexp); // exposition is 1/t, real (decimal) if exposition >1 s
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &Clave9);
if(Clave5c>0) {gamm=Clave5c;}
;
;
ugamm=1/gamm;
iso=Clave6;
printf("Remember: The 3 bmp pictures need to be: well aligned, non-compressed, s-rgb colors, and of the same width, height! \n");
printf("The output res.bmp will have the same headings as the central picture dib1.bmp\n");
printf("Key: 1,2,3,5c,6,nab,timexp,Clave9 : %ld %ld %ld %lf %lf %lf %lf %ld \n",Clave1,Clave2,Clave3,Clave5c,Clave6,nab,timexp,Clave9);
PunteroImagenInicial = fopen("dib1.bmp","rb");
PunteroImagenInicial1 = fopen("dib2.bmp","rb");
PunteroImagenInicial2 = fopen("dib3.bmp","rb");
PunteroImagenFinal = fopen("res.bmp", "wb");
; // Read from dib1.bmp, check BM, obtain width heigth, and move to start of data for all 3 files equal
b = fgetc(PunteroImagenInicial);
g = fgetc(PunteroImagenInicial);
fputc(b,PunteroImagenFinal);
fputc(g,PunteroImagenFinal);
printf("1, 2 (is BM?)): %c %c \n",b,g); //if not BM, the file might be erroneous; anyway, the script tries to continue
b = fgetc(PunteroImagenInicial);
g = fgetc(PunteroImagenInicial);
r = fgetc(PunteroImagenInicial);
bbc = fgetc(PunteroImagenInicial);
fputc(b,PunteroImagenFinal);
fputc(g,PunteroImagenFinal);
fputc(r,PunteroImagenFinal);
fputc(bbc,PunteroImagenFinal);
b = fgetc(PunteroImagenInicial);
g = fgetc(PunteroImagenInicial);
r = fgetc(PunteroImagenInicial);
bbc = fgetc(PunteroImagenInicial);
fputc(b,PunteroImagenFinal);
fputc(g,PunteroImagenFinal);
fputc(r,PunteroImagenFinal);
fputc(bbc,PunteroImagenFinal);
bb= fgetc(PunteroImagenInicial);
gg = fgetc(PunteroImagenInicial);
rr = fgetc(PunteroImagenInicial);
bmax = fgetc(PunteroImagenInicial);
fputc(bb,PunteroImagenFinal);
fputc(gg,PunteroImagenFinal);
fputc(rr,PunteroImagenFinal);
fputc(bmax,PunteroImagenFinal);
b = fgetc(PunteroImagenInicial);
g = fgetc(PunteroImagenInicial);
r = fgetc(PunteroImagenInicial);
bbc = fgetc(PunteroImagenInicial);
fputc(b,PunteroImagenFinal);
fputc(g,PunteroImagenFinal);
fputc(r,PunteroImagenFinal);
fputc(bbc,PunteroImagenFinal);
b = fgetc(PunteroImagenInicial);
g = fgetc(PunteroImagenInicial);
r = fgetc(PunteroImagenInicial);
bbc = fgetc(PunteroImagenInicial);
fputc(b,PunteroImagenFinal);
fputc(g,PunteroImagenFinal);
fputc(r,PunteroImagenFinal);
fputc(bbc,PunteroImagenFinal);
anchura=b+256*(g+256*(r+256*bbc));
b = fgetc(PunteroImagenInicial);
g = fgetc(PunteroImagenInicial);
r = fgetc(PunteroImagenInicial);
bbc = fgetc(PunteroImagenInicial);
fputc(b,PunteroImagenFinal);
fputc(g,PunteroImagenFinal);
fputc(r,PunteroImagenFinal);
fputc(bbc,PunteroImagenFinal);
altura=b+256*(g+256*(r+256*bbc));
// remaining start of image data -26
k=bb+256*(gg+256*(rr+256*bmax));
j=k-26;
for (i=0;i<j;i++) {    //copy remaining part of bmp  initial part
b = fgetc(PunteroImagenInicial);
fputc(b,PunteroImagenFinal);
}
;	//move to starting image data
fseek(PunteroImagenInicial,bb+256*(gg+256*(rr+256*bmax)),SEEK_SET);  //goes directly to start of picture data. Assumed rgb bitmap!
fseek(PunteroImagenInicial1,bb+256*(gg+256*(rr+256*bmax)),SEEK_SET);  //goes directly to start of picture data. Assumed rgb bitmap!
fseek(PunteroImagenInicial2,bb+256*(gg+256*(rr+256*bmax)),SEEK_SET);  //goes directly to start of picture data. Assumed rgb bitmap!
; // ATTENTION Write new picture file
falt=altura;
fanch=anchura;
f0alt=0.04*falt;
fanch1=fanch-2;
falt1=falt-2;
rEV=Clave2;
if (Clave2==0) {printf("Jump in EV between pictures \n");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%lf", &rEV);
}  // end Clave2==0
;
;
rrEV=pow(2,rEV);  //find rreV
rluminp=0;
ev=-200;
lmax=0;
;// out()  // No. points
if (Clave9>0) {
for(i=1; i<=Clave9; i++)
        {
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &xl[i]);
   fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &yl[i]);
};  // end loop i Clave9
};  // end if Clave9>0
; //  out()
;
printf("Rectangles first point included, last point no \n");   //3 cops
for(ir=0;ir<3;ir++)
{
    fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &xini1[ir]);
    fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &xefe1[ir]);
    fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &yini1[ir]);
    fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &yefe1[ir]);
    printf("Rectangle %ld  corners xini, xefe, yini, yefe: %ld %ld %ld %ld \n",ir+1,xini1[ir],xefe1[ir],yini1[ir],yefe1[ir]);
}
;
    fgets(line, sizeof(line), PunteroClave);
    sscanf(line, "%ld", &maxlimit);
Vmaxlimit=maxlimit;  // End starting and reading
factorL=rluminp*rvpunt/765;
;
fclose(PunteroClave);
        timexp=1.0/timexp;  //conversions
        ev=log((nab*nab/timexp)*100/iso)/log(2);
if(factorL==0){factorL=1;};
; //factorL used to give values in digit if non-zero code, or in units from calibration //original 0.125 from camera-> 0.167?
;
;
if (ev>-19) {factorL=(1.0/(100.0/2.0))*pow(2,ev)*0.125;
};
;
; //printf("ISO, nab, timexp %f %f %f \n",iso,nab,timexp); //printf("ev, rrEV, factorL: %f %f %f \n",ev,rrEV,factorL);
// correction factorL reference for gamma (155 digit camera) different from point where luminance is calculated
// (215 digit camera or 319.025 (absolute resp. 155 reference) digit corrected for gamma compression from camera)
;
factorL=factorL*0.5755;  //// CALIBRATION
maxcont=rrEV*155*pow((255/155),gamm);
;  // first file normal (EV), then (EV-rEV), later (EV+rEV) Read and gamma-decompress
for(i=0 ; i<altura ; i++)
{for(j=0 ; j<anchura ; j++)
{
Azul[i][j] = fgetc(PunteroImagenInicial); // B
Verde[i][j] =fgetc(PunteroImagenInicial); // G
Rojo[i][j] = fgetc(PunteroImagenInicial); // R
Azul1[i][j] = fgetc(PunteroImagenInicial1); // B
Verde1[i][j] =fgetc(PunteroImagenInicial1); // G
Rojo1[i][j] = fgetc(PunteroImagenInicial1); // R
Azul2[i][j] =  fgetc(PunteroImagenInicial2); // B
Verde2[i][j] = fgetc(PunteroImagenInicial2); // G
Rojo2[i][j] =  fgetc(PunteroImagenInicial2); // R
;//decompress gamma     HDR
aargb=(Azul[i][j]/155.0);
Azu[i][j]=155.0*pow(aargb,gamm);
if(Azul[i][j]>210) {aargb=(Azul1[i][j]/155.0);
        Azu[i][j]=rrEV*155.0*pow(aargb,gamm);
                                        };
;
;
if (Azul[i][j]<40) {aargb=(Azul2[i][j]/155.0);
                                        Azu[i][j]=(155.0/rrEV)*pow(aargb,gamm);
                                        };
;
;
aargb=(Verde[i][j]/155.0);
Verd[i][j]=155.0*pow(aargb,gamm);
if(Verde[i][j]>210) {aargb=(Verde1[i][j]/155.0);
                                        Verd[i][j]=rrEV*155.0*pow(aargb,gamm);
                                        };
;
;
if (Verde[i][j]<40) {aargb=(Verde2[i][j]/155.0);
                                        Verd[i][j]=(155.0/rrEV)*pow(aargb,gamm);
                                        };
;
;
aargb=(Rojo[i][j]/155.0);
Roj[i][j]=155.0*pow(aargb,gamm);
if(Rojo[i][j]>210) {aargb=(Rojo1[i][j]/155.0);
                                        Roj[i][j]=rrEV*155.0*pow(aargb,gamm);
                                        };
;
;
if (Rojo[i][j]<40) {aargb=(Rojo2[i][j]/155.0);
                                        Roj[i][j]=(155.0/rrEV)*pow(aargb,gamm);
                                        };
;
;  // average
su=(Roj[i][j]+Verd[i][j]+Azu[i][j])/3.;
lc2r=lc2r+Roj[i][j];
lc2g=lc2g+Verd[i][j];
lc2b=lc2b+Azu[i][j];
lc2=lc2+su;
if(lmax<su) {lmax=su;};
;
;
};  // end j loop
};  // end i loop
fclose(PunteroImagenInicial);
fclose(PunteroImagenInicial1);
fclose(PunteroImagenInicial2);
;// end lecture  bmp files
PunteroDatos = fopen("Lumi.dat","wa");
;
printf("Picture case, EV, rrEV, factorL, maxcont, lmax  %lf %lf %lf %lf %lf \n",ev,rrEV,factorL,maxcont,lmax);
printf("Computing... \n");
//Attention! R G B over 255 steps 
;// out {} no parentheses
ss=0;
ssr=0;
ssg=0;
ssb=0;
flc2=lc2/(fanch*falt);
flc2r=lc2r/(fanch*falt);
flc2g=lc2g/(fanch*falt);
flc2b=lc2b/(fanch*falt);
;
for(i=0 ; i<altura ; ++i)
{for(j=0 ; j<anchura ; ++j)
{     su=(Azu[i][j]+Verd[i][j]+Roj[i][j])/3;
ss=ss+(su-flc2)*(su-flc2);
ssr=ssr+(flc2r-Roj[i][j])*(flc2r-Roj[i][j]);
ssg=ssg+(flc2g-Verd[i][j])*(flc2g-Verd[i][j]);
ssb=ssb+(flc2b-Azu[i][j])*(flc2b-Azu[i][j]);
//end calculus desvest
};    // end j loop
};    // end i loop
;
// out {}
;
printf("Total average value flc2 (base, uncompressed), cd/m2: %lf %lf \n",flc2,flc2*factorL);
printf("Total average   Red    flc2r (cd/m2) : %lf \n",flc2r*factorL/3);
printf("Total average   Green  flc2g (cd/m2) : %lf \n",flc2g*factorL/3);
printf("Total average   Blue   flc2b (cd/m2) : %lf \n",flc2b*factorL/3);
printf("Computing... \n");
ss=sqrt(ss/(falt*fanch));
ssr=sqrt(ssr/(falt*fanch));
ssg=sqrt(ssg/(falt*fanch));
ssb=sqrt(ssb/(falt*fanch));
        fprintf(PunteroDatos,"Analysis of pictures \n");
        fprintf(PunteroDatos,"Pictures in dib1.bmp, dib2.bmp, dib3.bmp \n");
        fprintf(PunteroDatos, " \n");
        fprintf(PunteroDatos,"Input keys: C1, SaltEv, Nbands, gamm, ASA/ISO, Nab, texp, Np \n");
        fprintf(PunteroDatos,"%ld %ld %ld %lf %lf %lf %lf %ld \n",Clave1,Clave2,Clave3,Clave5c,Clave6,nab,timexp,Clave9);
	if(Clave9>0) 	{
        fprintf(PunteroDatos,"No. points find average (9p)  %ld \n",Clave9);
		for (i=1; i<=Clave9; ++i)
 	 {fprintf(PunteroDatos, "No.Points,  x , y: %ld %ld %ld \n",i,xl[i],yl[i]);
	 };
};
;
;
        fprintf(PunteroDatos, " \n");
for (i=0; i<3;i++)
{fprintf(PunteroDatos, "Rectangles to average, coord.: N.rect, xini,xefe; yini,yefe %ld %ld %ld %ld %ld \n",i+1,xini1[i],xefe1[i],yini1[i],yefe1[i]);
};
;
        fprintf(PunteroDatos,"\n");
        fprintf(PunteroDatos,"Computation with luminances in cd/m2 \n");
        fprintf(PunteroDatos,"\n");
        fprintf(PunteroDatos,"If it is not calibred, scale of luminances from 0 to 255*rrEV \n");
        fprintf(PunteroDatos,"If it is calibred, Value and Luminance of point: %lf %lf coords x, y: %0.f %0.f \n",rvpunt,rluminp,rxpat,rypat);
        fprintf(PunteroDatos,"\n");
        fprintf(PunteroDatos,"If data from picture, ev, rrEV, factorL(over 255): %lf %lf %lf %lf \n",ev,rrEV,factorL);
        fprintf(PunteroDatos,"lmax, from one maximum: %lf %lf \n",lmax,rrEV*155.*pow(255./155.,gamm));
        fprintf(PunteroDatos,"\n");
fprintf(PunteroDatos,"The picture has average value (non-compressed): %lf \n",flc2*factorL);
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos, "Normalized Luminance values at right of the lower bar (cd/m2): %lf \n",Vmaxlimit);
	    fprintf(PunteroDatos, " \n");
        fprintf(PunteroDatos, " \n");
        fprintf(PunteroDatos,"Picture of height*width:  %0.f  %0.f \n",falt,fanch);
        fprintf(PunteroDatos, " \n");
fprintf(PunteroDatos,"Average luminance and standard deviation (cd/m2, all picture): %lf %lf \n",flc2*factorL,ss*factorL);
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos,"Average  R  and  standard  deviation  (cd/m2): %lf %lf \n",flc2r*factorL/3,ssr*factorL/3);
fprintf(PunteroDatos,"Average  G  and  standard  deviation  (cd/m2): %lf %lf \n",flc2g*factorL/3,ssg*factorL/3);
fprintf(PunteroDatos,"Average  B  and  standard  deviation  (cd/m2): %lf %lf \n",flc2b*factorL/3,ssb*factorL/3);
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos,"r,  g,  b  (unitary) : %lf  %lf  %lf  \n",flc2r/flc2/3,flc2g/flc2/3,flc2b/flc2/3);
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos," \n");  //out
printf("Writing  results... \n");
for(ir=0; ir<3; ir++)    // rectangles
{xini=xini1[ir];
xefe=xefe1[ir];
yini=yini1[ir];
yefe=yefe1[ir];
rxini=xini;
rxefe=xefe;
ryini=yini;
ryefe=yefe;
npromirect=0;
rpromirect=0;
rpromirectr=0;
rpromirectg=0;
rpromirectb=0;
for(i=yini ; i<yefe ; ++i)
{for(j=xini ; j<xefe ; ++j)
 {
 ;		   rpromirectr=rpromirectr+Roj[i][j];
		   rpromirectg=rpromirectg+Verd[i][j];
		   rpromirectb=rpromirectb+Azu[i][j];
		   npromirect=npromirect+1;
};      // end j loop
};      // end i loop
;
rnpromirect=npromirect;
rpromirect=((rpromirectr+rpromirectg+rpromirectb)/rnpromirect);
rpromirectr=(rpromirectr/rnpromirect);
rpromirectg=(rpromirectg/rnpromirect);
rpromirectb=(rpromirectb/rnpromirect);
rdesvrect=0;
rdesvrecr=0;
rdesvrecg=0;
rdesvrecb=0;  // stdesv
for(i=yini ; i<yefe ; ++i)
{for(j=xini ; j<xefe ; ++j)
		{        su=(Azu[i][j]+Verd[i][j]+Roj[i][j]);
				rdesvrect=rdesvrect+(su-rpromirect)*(su-rpromirect);
				rdesvrecr=rdesvrecr+(rpromirectr-Roj[i][j])*(rpromirectr-Roj[i][j]);
				rdesvrecg=rdesvrecg+(rpromirectg-Verd[i][j])*(rpromirectg-Verd[i][j]);
				rdesvrecb=rdesvrecb+(rpromirectb-Azu[i][j])*(rpromirectb-Azu[i][j]);
};
}; //close i,j
;
rdesvrect=sqrt(rdesvrect/rnpromirect);
rdesvrecr=sqrt(rdesvrecr/rnpromirect);
rdesvrecg=sqrt(rdesvrecg/rnpromirect);
rdesvrecb=sqrt(rdesvrecb/rnpromirect);
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos,"Considered   Rectangle   #   %ld \n",ir+1);
fprintf(PunteroDatos,"x  Interval: %0.f  %0.f \n",rxini,rxefe);
fprintf(PunteroDatos,"y  Interval: %0.f  %0.f \n",ryini,ryefe);
fprintf(PunteroDatos,"Number of considered points: %0.f \n",rnpromirect);
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos,"Average and standard deviation L on the rectangle: %lf %lf \n",rpromirect*factorL,rdesvrect*factorL);
fprintf(PunteroDatos,"Average and standard deviation R on the rectangle: %lf %lf \n",rpromirectr*factorL,rdesvrecr*factorL);
fprintf(PunteroDatos,"Average and standard deviation G on the rectangle: %lf %lf \n",rpromirectg*factorL,rdesvrecg*factorL);
fprintf(PunteroDatos,"Average and standard deviation B on the rectangle: %lf %lf \n",rpromirectb*factorL,rdesvrecb*factorL);
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos,"Coordinates r, g, b unitary: %lf %lf %lf \n",rpromirectr/(rpromirectr+rpromirectg+rpromirectb),rpromirectg/(rpromirectr+rpromirectg+rpromirectb),rpromirectb/(rpromirectr+rpromirectg+rpromirectb));
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos," \n");
}  //close ir (0, 1, 2)
;
;
if(Clave9>0)
{         for (j=1; j<=Clave9; j++)
        {
rxl=xl[j];
ryl=yl[j];
PL=0;
PR=0;
PG=0;
PB=0;
n9=0;
for (i=(yl[j]-1); i<=(yl[j]+1);i++)
	{for (k=(xl[j]-1);k<=(xl[j]+1);k++)
		{PL=PL+(Roj[i][k]+Verd[i][k]+Azu[i][k]);
		PR=PR+Roj[i][k];
		PG=PG+Verd[i][k];
		PB=PB+Azu[i][k];
		n9=n9+1;
        };
    };
;
PL=PL/n9;
PR=PR/n9;
PG=PG/n9;
PB=PB/n9;
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos, "Results 3 pictures (dib1.bmp, dib2.bmp, dib3.bmp) \n");
fprintf(PunteroDatos, "Point xl yl from left, down: %ld %ld \n",xl[j],yl[j]);
fprintf(PunteroDatos, "Values R,G,B, Lumin (cd/m2): %lf %lf %lf %lf \n",PR*factorL/3,PG*factorL/3,PB*factorL/3,PL*factorL/3);
printf(" \n");
printf("Results 3 pictures (dib1.bmp, dib2.bmp, dib3.bmp) \n");
printf("Point xl yl from left, below: %ld %ld \n",xl[j],yl[j]);
printf("Values R,G,B, Lumin  (cd/m2): %lf %lf %lf %lf \n",PR*factorL/3,PG*factorL/3,PB*factorL/3,PL*factorL/3);
PL=0;
PR=0;
PG=0;
PB=0;
n9=0;
for (i=(yl[j]-1); i<=(yl[j]+1);i++)
	{for (k=(xl[j]-1);k<=(xl[j]+1);k++)
		{
aargb=(Rojo[i][k]/155.0);
R1=155.0*pow(aargb,gamm);
aargb=(Verde[i][k]/155.0);
G1=155*pow(aargb,gamm);
aargb=(Azul[i][k]/155.0);
B1=155*pow(aargb,gamm);
		PR=PR+R1;
		PG=PG+G1;
		PB=PB+B1;
		PL=PL+R1+G1+B1;
		n9=n9+1;
    	};
   };
;
PL=PL/n9;
PR=PR/n9;
PG=PG/n9;
PB=PB/n9;
fprintf(PunteroDatos," \n");
fprintf(PunteroDatos,"Results 1 picture (dib1.bmp) \n");
fprintf(PunteroDatos, "Point xl yl from left, below: %ld %ld \n",xl[j],yl[j]);
fprintf(PunteroDatos, "Values R,G,B, Lumin (cd/m2) : %lf %lf %lf %lf \n",PR*factorL/3,PG*factorL/3,PB*factorL/3,PL*factorL/3);
printf(" \n");
printf("Results 1 picture (dib1.bmp) \n");
printf("Point xl yl from left, below: %ld %ld \n",xl[j],yl[j]);
printf("Values R,G,B, Lumin  (cd/m2): %lf %lf %lf %lf \n",PR*factorL/3,PG*factorL/3,PB*factorL/3,PL*factorL/3);
; //actual 1 picture
}; // end loop j   from 1 to clave9!
;
}; //end if Clave9
;
;
fprintf(PunteroDatos,"\n");
fprintf(PunteroDatos,"\n");
rescala2=Clave3-1; // no. bars L   //assign limits of the L bars // Remains to write scale of bars to file!
escalalimit=1;  //rescala2 is no. of bars - 1
if(rescala2<=2) {rescala2=2;
limit[0]=0;
limit[1]=167;
limit[2]=255;
}
;
;
if(rescala2==3) {limit[0]=0;
limit[1]=110;
limit[2]=208;
limit[3]=255;
}
;
;
if(rescala2==4) {limit[0]=0;
limit[1]=110;
limit[2]=167;
limit[3]=208;
limit[4]=255;
}
;
;
if(rescala2==5) {limit[0]=0;
limit[1]=110;
limit[2]=167;
limit[3]=225;
limit[4]=240;
limit[5]=255;
}
;
;
if(rescala2==6) {limit[0]=0;
limit[1]=110;
limit[2]=167;
limit[3]=208;
limit[4]=225;
limit[5]=240;
limit[6]=255;
}
;
;
if(rescala2==7) {limit[0]=0;
limit[1]=71;
limit[2]=167;
limit[3]=189;
limit[4]=208;
limit[5]=225;
limit[6]=240;
limit[7]=255;
}
;
;
if(rescala2==8) {limit[0]=0;
limit[1]=71;
limit[2]=141;
limit[3]=167;
limit[4]=189;
limit[5]=208;
limit[6]=225;
limit[7]=240;
limit[8]=255;
}
;
;
if (rescala2>=9) {rescala2=9;
limit[0]=0;
limit[1]=71;
limit[2]=110;
limit[3]=141;
limit[4]=167;
limit[5]=189;
limit[6]=208;
limit[7]=225;
limit[8]=240;
limit[9]=255;
}  //max 9+1 bars
;
;
escala2=rescala2;
escalalimit=1;
factor=1; // attention if Vmaxlimit=0, then authomatic scale; if negative, inverted scale  
if (Vmaxlimit>0)
{escalalimit= Vmaxlimit/factorL;  // Vmaxlimit/factorL would be maxcount in place of 255; attention gamma compression, is max 463,436
factor=155.*pow(255./155.,gamm)/escalalimit;
};
;
;
fprintf(PunteroDatos, "\n");  //attention scale L noted on the bars and picture
fprintf(PunteroDatos, "Values L bands from the picture (first band from 0 to first value), with factorL %lf: \n",factorL);   //OJO limit es comprimido!!! i factorL
for (i=0; i<=escala2; ++i)
        {ri=i;
        aargb=limit[i]/155.0+1e-10;   ///155!!!!
        R1=155.0*pow(aargb,gamm);  //*255/463.4;
        fprintf(PunteroDatos, " %0.f    %lf  \n",ri,R1*factorL/factor);    //R es sobre 463.436 i no sobre 255   Ull canvi Lmax
        };  // fi bucle i
        ;
fprintf(PunteroDatos," \n");
; // prepare final image, gamma compression (go to s-RGB space)  
;
	        for(i=0 ; i<altura ; i++)
{for(j=0 ; j<anchura ; j++)
{aargb=(Azu[i][j]*factor/155.0);
Azu[i][j]=155.0*pow(aargb,ugamm);
aargb=(Verd[i][j]*factor/155.0);
Verd[i][j]=155.0*pow(aargb,ugamm);
aargb=(Roj[i][j]*factor/155.0);
Roj[i][j]=155.0*pow(aargb,ugamm);
;
};    // end j loop
;
};    // end i loop
;
printf("Writing final image \n");
// rescala2 is no. of divisions
                                for(i=0 ; i<f0alt; ++i)
        {for(j=0 ; j<anchura ; ++j)
                        {aa=limit[((escala2+1)*j)/anchura];
 						fputc(aa,PunteroImagenFinal);
                        fputc(aa,PunteroImagenFinal);
                        fputc(aa,PunteroImagenFinal);
                        };   // end j loop
         ;
        };    // end i loop
;
;
for(i=f0alt ; i<altura; ++i)
   {for(j=0 ; j<anchura ; ++j)
       {
	   su=(Roj[i][j]+Verd[i][j]+Azu[i][j])/3;
	   aa=0;
        for (k=1; k<=escala2;++k)
           {if (su>=limit[k]) {aa=limit[k];};
            ;
            ;
           };   // end k loop   //                       if(aa>255) {aa=255;};  //eventual protection
        fputc(aa,PunteroImagenFinal);
        fputc(aa,PunteroImagenFinal);
        fputc(aa,PunteroImagenFinal);
       };    // end j loop
   };    // end i loop
; // end of writing bmp resul file, close all
fclose(PunteroDatos);
fclose(PunteroImagenFinal);
printf("End of the script, code 0 is OK, press Intro\n");  // c=getchar();
} // END


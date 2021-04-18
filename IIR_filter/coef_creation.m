%% Function to generate a 4th order lowpass IIR 
[B,A]=ellip(4,0.25,10,0.25);
freqz(B,A);
z=roots(B);
p=roots(A);

%% I create the transfer function as a product of two 2nd order transfer functions
A1 = poly([0.6715 + 0.7012i 0.6715 - 0.7012i]);
B1 = poly([0.2697 + 0.9629i 0.2697 - 0.9629i]);
A2 = poly([0.4759 + 0.4613i 0.4759 - 0.4613i]);
B2 = poly([0.6684 + 0.7438i 0.6684 - 0.7438i]);

X=zeros(1,500);
X(1)=1;

% Gain factor calculations to avoid overflow
f1 = filter(B1,A1,X);
f2 = filter(B2,A2,X);
G1 = 1/abs(sum(f1));
G2 = 1/abs(sum(f2));
Gol = G1*G2;

A1c = twocomplement(A1/2);
A2c = twocomplement(A2/2);
B1c = twocomplement(B1/2);
B2c = twocomplement(B2/2);
G1c = twocomplement(G1/2);
G2c = twocomplement(G2/2);

%% Header file creation
coefs = fopen('coefs.h','w');
fprintf(coefs ,'#define G1_c %d\n',G1c);
fprintf(coefs,'#define G2_c %d\n',G2c);
fprintf(coefs,'#define a1_1 %d\n',A1c(2));
fprintf(coefs,'#define a2_1 %d\n',A1c(3));
fprintf(coefs,'#define b1_1 %d\n',B1c(2));
fprintf(coefs,'#define b2_1 %d\n',B1c(3));
fprintf(coefs,'#define a1_2 %d\n',A2c(2));
fprintf(coefs,'#define a2_2 %d\n',A2c(3)); 
fprintf(coefs,'#define b1_2 %d\n',B2c(2));
fprintf(coefs,'#define b2_2 %d\n',B2c(3)); 
 
fclose('all');


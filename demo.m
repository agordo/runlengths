%% Compile the mex file
mex -largeArrayDims -O CFLAGS="\$CFLAGS -O3 -ffast-math -std=c99" Runlength_c.c -o Runlength_c


%% Read Image. Both color or grayscal are accepted
imGray = rgb2gray(imread('sample.png'));

%% Compute descriptors
d = Runlength(imGray);

%% Display result
bar(d);


function [ desc ] = Runlength(im,  npixels,pyramid)
%RUNLENGTH Summary of this function goes here
% Computes the Runlength descriptor of an image as in [1]
% im is a color or grayscale image
% pyramid is the spatial pyramid partitioning in [x1,x2,y1,y2] format. By default, 1x1+2x2+4x4.
% npixels is the maximum number of pixels of the image. If the image is
% larger than npixels, it is rescaled preserving the aspect ration.

% [1] Large-scale document image retrieval and classification with
% runlength histograms and binary embeddings. A. Gordo, F. Perronnin, and
% E. Valveny. In Pattern Recognition, 2012.


if nargin < 2
    npixels=5e5;
end

if nargin < 3
    pyramid = [0,    1,     0,    1; % 1x1
              0,     0.5,   0,    0.5; %2x2
              0,     0.5,   0.5,  1;
              0.5,   1,     0,    0.5;
              0.5,   1,     0.5,  1;
              0,     0.25,  0,    0.25; %4x4
              0,     0.25,  0.25, 0.5;
              0,     0.25,  0.5,  0.75;
              0,     0.25,  0.75, 1;
              0.25,  0.5,   0,    0.25;
              0.25,  0.5,   0.25, 0.5;
              0.25,  0.5,   0.5,  0.75;
              0.25,  0.5,   0.75, 1;
              0.5,   0.75,  0,    0.25;
              0.5,   0.75,  0.25, 0.5;
              0.5,   0.75,  0.5,  0.75;
              0.5,   0.75,  0.75, 1;
              0.75,  1,     0,    0.25;
              0.75,  1,     0.25, 0.5;
              0.75,  1,     0.5,  0.75;
              0.75,  1,     0.75, 1];
end



[m,n,c] = size(im);
% Go grayscale
if c~=1
    im = rgb2gray(im);
end
% Resize image to npixels
factor =  sqrt(npixels/(m*n));
im = imresize(im, factor);
% Binarize. Be sure image is int32
im = int32(im2bw(im, graythresh(im)));

[m,n,c] = size(im);


%% For each partition, extract the image and compute the descriptor
D=zeros(72,size(pyramid, 1));
% Pyramid
for i=1:size(pyramid, 1)
    % Get the image coords
    coords = pyramid(i,:).* [ n,n,m,m];
    % Be sure it is inside the image
    coords([1,3]) = max(floor(coords([1,3])), [1,1]);
    coords([2,4]) = min(ceil(coords([2,4])), [n,m]);
    % Compute descriptor
    D(:,i) = Runlength_c(im(coords(3):coords(4),coords(1):coords(2)));
end
% Flat and normalize
desc = D(:);
desc = sqrt(desc/sum(desc));
desc(isnan(desc)) = 0;



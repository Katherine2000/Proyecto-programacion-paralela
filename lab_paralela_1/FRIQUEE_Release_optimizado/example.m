%% An example script to demonstrate FRIQUEE feature extraction and prediction of image quality.

% This script performs two tasks:

% 1 : Extracts FRIQUEE features

% 2 : Loads a learned model trained on all the images of LIVE Challenge Database and predicts the quality of the given example image. The quality is predicted on a scale of 0-100, where 0 represents the worst score and 1 represents the best score.
%Dependencies

%  The assumption here is that you have libsvm installed and
% svmpredict binary built
%profile on;
clear;
addpath('include/');
addpath('src/');
tic;
load('data/friqueeLearnedModel.mat');
n_frames = 497;
p = Par(n_frames);
scores = zeros(n_frames,1);
parfor i= 1:n_frames
    % Read an image
    Par.tic;
    name = 'Pictures';
    number = num2str(i);
    ext = '.jpg';
    frame_name = strcat(name,number,ext);
    img = imread(strcat('data/video2/',frame_name));

    % Extract FRIQUEE-ALL features of this image
    testFriqueeFeats = extractFRIQUEEFeatures(img);

    % Load a learned model
    % load('data/friqueeLearnedModel.mat');

    % Scale the features of the test image accordingly.
    % The minimum and the range are computed on features of all the images of
    % LIVE Challenge Database
    testFriqueeALL = testFeatNormalize(testFriqueeFeats.friqueeALL, friqueeLearnedModel.trainDataMinVals, friqueeLearnedModel.trainDataRange);

    qualityScore = svmpredict (0, double(testFriqueeALL), friqueeLearnedModel.trainModel, '-b 1 -q');
    scores(i) = qualityScore;
    p(i) = Par.toc;
end
stop(p);
plot(p);
disp('La media de los scores es:');
media = mean(scores);
disp(media);
desviacion = std(scores);
ans_menos = media-desviacion;
ans_mas = media+desviacion;
res = [ans_menos,ans_mas];
disp('El score final del video está entre:');
disp(res);
toc;
%profile viewer;
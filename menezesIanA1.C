#include <stdio.h>
#include "givenA1.h"

//task 1
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]) {

    FILE *file = fopen(fName,"r");

    if (file == NULL) {
        return -1;
    }

    for(int i = 0; i < NUM_SAMPLES; i++) {
        fscanf(file, "%s ", dataZoo[i].animalName); // reads a string from the file and stores it in the animalName member of the struct Animal in datazoo array

        for(int j = 0; j < NUM_FEATURES; j++) {
            fscanf(file, "%d ", &dataZoo[i].features[j]);  // to read NUM_FEATURES integer values from the file and store them in the features array of the the Animal structure
        }

        fscanf(file, "%d", &dataZoo[i].classLabel); // fscanf is used to read the classLabel value from the file and store it in the classLabel member of the current Animal structure.


    }
    return 1;
}

// task 2: This function generates the mean and mode of the feature
int generateStatisticsFeatureX(struct Animal dataZoo[NUM_SAMPLES], int whichFeature, float *mean, int *mode) {
    if (whichFeature < 1 || whichFeature > NUM_FEATURES) {
        return -1; // Return -1 for an invalid feature number
    }

    float sum = 0.0;
    int count = 0;
    int frequencies[NUM_SAMPLES] = {0};

    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += dataZoo[i].features[whichFeature - 1]; 
        frequencies[dataZoo[i].features[whichFeature - 1]]++;
        count++;
    }

    *mean = sum / count; // Calculate mean

    int maxFrequency = 0;
    int modeValue = -1;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        if (frequencies[i] > maxFrequency) {
            maxFrequency = frequencies[i];
            modeValue = i;
        }
    }

    *mode = modeValue; // Assign the mode value

    return 0; 
}


// task 3: This function takes the zoo dataset and displays its class distribution as a histogram
void classDistribution(struct Animal dataZoo[NUM_SAMPLES]) {
    int count = 0;
    int maxClass = 0;
    int classSize[7] = {0,0,0,0,0,0,0};

    for (int i = 0; i < NUM_SAMPLES; i++) {
        count = 0;

        for (int j = 0; j < NUM_SAMPLES; j++) {
            if (dataZoo[j].classLabel == dataZoo[i].classLabel) {
                count++;
            }
        }

        classSize[dataZoo[i].classLabel - 1] = count;  // Populate classSize[] with # of animals in each class

        if (count > maxClass) {  // Finds the max class label
            maxClass = count;
        }
    }

    for (int i = maxClass + 1; i > 0; i--) {  // Prints histogram
        for (int j = 0; j < 7; j++) {
            if (classSize[j] == i - 1) {  // Prints total value at top of column
                printf(" (%d)", classSize[j]);
            }

            if (classSize[j] >= i) {
                printf("  *\t");
            } else {
                printf("  \t");
            }
        }

        printf("\n");
    }

    for (int i = 1; i < 8; i++) {  // Prints class labels at bottom
        printf("Class %d\t", i);
    }
    printf("\n");
}

//task 4 : This function computes and returns the Euclidean distance between 2 arrays, each with 16 features

float euclideanDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]) {

    float distance = 0;
    float diff = 0;
    float sum = 0;

    for (int i = 0; i < NUM_FEATURES; i++) {

        diff = vector1[i] - vector2[i];
        sum += diff * diff;
    
        distance = sqrt(sum);
    }

    return distance;

}

// task 5 : This function calculates the hamming distance between two vectors

int hammingDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {
    int distance = 0;

    // Calculate the Hamming distance by comparing corresponding values
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] != vector2[i]) {
            distance++;
        }
    }

    return distance;
}    


//task 6 :

float jaccardSimilarity(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {
    int oneOneMatches = 0;
    int zeroZeroMatches = 0;

    // Calculate the number of 1-1 matches and 0-0 matches
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] == 0 && vector2[i] == 0) { // check if both vectors are zero
            zeroZeroMatches++;
        } else if (vector1[i] == vector2[i]) {   // check if the vectors are same
            oneOneMatches++;
        }
    }

    // Calculate Jaccard Similarity
    float similarity = (float)oneOneMatches / (NUM_FEATURES - zeroZeroMatches);

    return similarity;
}


// task 7
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){

    float distance[NUM_SAMPLES];
    int i, j, tempIndices;
    float tempDist;
    
  

    for (int i = 0; i < NUM_SAMPLES; i++) {            // deciding what distance function to use
        if (whichDistanceFunction == 1) {
            distance[i] = euclideanDistance (dataZoo[i].features, newSample);
        } else if (whichDistanceFunction == 2) {
            distance[i] = hammingDistance (dataZoo[i].features, newSample);
        } else if (whichDistanceFunction == 3) {
            distance[i] = jaccardSimilarity (dataZoo[i].features, newSample);
        }
    }

    for (int i = 0; i < NUM_SAMPLES; i++) {           // populating kNearNeighbors
        kNearestNeighbors[i] = i; 
    }


    // NEW sorting function from chatgpt, https://chat.openai.com/


    for (i = 0; i < NUM_SAMPLES; i++) {
        for (j = 0; j < NUM_SAMPLES - 1 - i; j++) {
            if (distance[j] > distance[j+1]) {
                tempDist = distance[j];                   // sorts out distances in increasing order
                distance[j] = distance[j+1];
                distance[j+1] = tempDist; 

                tempIndices = kNearestNeighbors[j];      // sorts out indices of kNearestNeighbors alongise the distances being sorted
                kNearestNeighbors[j] = kNearestNeighbors[j+1];
                kNearestNeighbors[j+1] = tempIndices;
            }
        }
    }

    

}



// task 8
int predictClass(struct Animal dataZoo[NUM_SAMPLES], int neighborsForNewSample[NUM_SAMPLES], int newSample[NUM_FEATURES], int k) {
    int classLabelsCount[NUM_CLASSES] = {0}; // Initialize an array to store the count of each class label
    int modeClassLabel = 0;

    // Count the occurrences of each class label among the neighbors
    for (int i = 0; i < k; i++) {
        int neighborIndex = neighborsForNewSample[i];
        int classLabel = dataZoo[neighborIndex].classLabel;
        if (classLabel >= 1 && classLabel <= NUM_CLASSES) {
            classLabelsCount[classLabel - 1]++;
        }
    }

    // Find the mode (most frequent class label)
    int maxCount = 0;
    for (int i = 0; i < NUM_CLASSES; i++) {
        if (classLabelsCount[i] > maxCount) {
            maxCount = classLabelsCount[i];
            modeClassLabel = i + 1; // Adjust to get the actual class label
        }
    }

    return modeClassLabel;
}

    



// task 9
float findAccuracy(struct Animal dataZoo[NUM_SAMPLES], struct Animal testData[NUM_TEST_DATA], int k) {
    int correctPredictions = 0;
    int predictedClass;
    float accuracy;

    for (int i = 0; i < NUM_TEST_DATA; i++) {
        // Find k-nearest neighbors for the current test sample
        int kNearestNeighbors[NUM_SAMPLES];
        int testFeatures[NUM_FEATURES];

        for (int j = 0; j < NUM_FEATURES; j++) {
            testFeatures[j] = testData[i].features[j];
        }

        findKNearestNeighbors(dataZoo, testFeatures, k, 1, kNearestNeighbors);

        // Predict the class for the current test sample
        predictedClass = predictClass(dataZoo, kNearestNeighbors, testFeatures, k);

        // Check if the prediction is correct
        if (testData[i].classLabel == predictedClass) {
            correctPredictions++;
        }
    }

    // Calculate accuracy
    accuracy = (float)correctPredictions / NUM_TEST_DATA * 100;
    return accuracy;
}







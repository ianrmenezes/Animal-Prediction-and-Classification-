#include "givenA1.h"


int main () {

    struct Animal dataZoo[NUM_SAMPLES];
    float mean;
    int mode;
    int v1[NUM_FEATURES]; 
    int v2[NUM_FEATURES];
    int whichFeature;
    int k ;
    int whichDistanceFunction = 1;
    int newSample [NUM_FEATURES] ;
    int neighborsForNewSample [NUM_SAMPLES] ;
    int kNearestNeighbors [NUM_SAMPLES];
    struct Animal testData [NUM_SAMPLES];
    char fName[30] = "a1Data.txt";
    int choice;
    


    //calling task 1, if the array was populationed properly.
      readFromFile (fName, dataZoo);


    do {
        printf("\nHere is the menu - enter a number between 1 and 9 \n\n");

        printf("1. Task 2: This function generates the mean and mode of the feature \n");

        printf("2. Task 3: This function takes the zoo dataset and displays its class distribution as a histogram\n");

        printf("3. Task 4: This function computes and returns the Euclidean distance between 2 arrays, each with 16 features\n");

        printf("4. Task 5: This function calculates the hamming distance between two vectors\n");

        printf("5. Task 6: This function calculates the jackard similarity between the two vectors\n");

        printf("6. Task 7: This function outputs an array called kNearestNeigbors that stores the indices of the k nearest neigbors of newSample using the given whichDistanceFunction\n");

        printf("7. Task 8: This function predicts its class and returns it given the k-nearest neighbors of a new data sample\n");

        printf("8. Task 9: This function prints the accuracy of the class labels given in task 8 \n");

        printf("9. Exit\n");

        printf("Enter your choice: ");  // validate your choice (should between 1 to 9)
        scanf("%d", &choice);

        if (choice < 1 || choice >9){
            printf("Invalid choice");
        }

        switch (choice){
        case 1 : //task 2
        printf("enter a value for whichFeature:" );
        scanf("%d",&whichFeature);
        
        generateStatisticsFeatureX (dataZoo, whichFeature, &mean, &mode);
      
        break;

        case 2: //task 3

        classDistribution (dataZoo);
        break;

        case 3: //task 4

        euclideanDistance (v1, v2);
        break;

        case 4: //task 5

        hammingDistance (v1, v2);
        break;

        case 5 : //task 6

        jaccardSimilarity (v1, v2);
        break;

        case 6: //task 7
        printf("enter value for k:");
        scanf("%d ",&k);

        findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);
        break;

        case 7: //task 8
        printf("enter a value for k:");
        scanf("%d", &k);

        predictClass(dataZoo,neighborsForNewSample, newSample, k);
        break;

        case 8: //task 9
        printf("enter a value for k:");
        scanf("%d", &k);

        findAccuracy(dataZoo, testData, k);
        break;

    default:
      printf("That is an invalid choice\n");
    }

  } while (choice != 9);
  
  return 0;
}














        


        
        /*for(int i = 0; i < NUM_SAMPLES; i++) {
            printf("%s    \t", dataZoo[i].animalName);

            for(int j = 0; j < 16; j++) {
                printf("%d ", dataZoo[i].features[j]);
            }

            printf("%d\n", dataZoo[i].classLabel);
        }
        */

   //printf("%d", dataZoo[2].classLabel);

   //testing task 2, if mean and mode are correct. IDK if they are right, its printing but still idk
       // generateStatisticsFeatureX (dataZoo, 14, &mean, &mode);
       // printf("%f \n%d", mean, mode);


    // task 3
      //  classDistribution (dataZoo);

    //testing task 4, euclidean distance, works, vectors are declared at the top.
      // printf("%.2f", euclideanDistance (v1, v2));

    //testing task 5, hamming distance, works,
      // printf("%.2f", hammingDistance (v1, v2)); 


    //testing task 6,
      //  printf("%.2f ",jaccardSimilarity (v1, v2));

    
    // Test Task 7: findKNearestNeighbors
  

    // Call the function
    //findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);
/*
    // Print kNearestNeighbors to verify
    printf("kNearestNeighbors: ");
    for (int i = 0; i < k; i++) {
        printf("%d ", kNearestNeighbors[i]);
    }
    printf("\n");
*/
    // Test Task 8: predictClass
   //int predictedClass = predictClass(dataZoo,neighborsForNewSample, newSample, k);
   //printf("Predicted Class: %d\n", predictedClass);

    // Test Task 9: findAccuracy
    //float accuracy = findAccuracy(dataZoo, testData, k);
    //printf("Accuracy: %.2f%%\n", accuracy);






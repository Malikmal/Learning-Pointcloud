#include <iostream>
#include "fann.h"

int main()
{
    //persamaan √(2x^2 + 1)
    const unsigned int num_input = 1;
    const unsigned int num_output = 1;
    const unsigned int num_layers = 4;
    const unsigned int num_neurons_hidden = 8; 
    const float desired_error = (const float) 0.0001; // break ketika error sudah lebih kecil dari ini
    const unsigned int max_epochs = 500000; //epoch iterasi
    const unsigned int epochs_between_reports = 1000; //jeda printing 
    struct fann *ann = fann_create_standard(num_layers, num_input,
        8,8, num_output);

    // fann_set_activation_function_hidden(ann, FANN_LINEAR); // set act func all hidden layer
    fann_set_activation_function_layer(ann, FANN_SIGMOID_SYMMETRIC, 1); //hidden layer ke 1
    fann_set_activation_function_layer(ann, FANN_LINEAR, 2); //hidden layer ke 2 
    fann_set_activation_function_output(ann, FANN_LINEAR);

    fann_train_on_file(ann, "testPersamaan.data", max_epochs,
        epochs_between_reports, desired_error);
    
    /***still cant work**/
    // fann_type input[1], *desired_output;
    // input[0] = 5;
    // // desired_output[0] = 7.1414;
    // desired_output[0] = (const float) 7.1414;
    // fann_test(ann, input, desired_output);
    // printf("hasil test : %f\n", desired_output);
    /****/

    fann_save(ann, "testPersamaan.net");

    fann_print_connections(ann);

    fann_destroy(ann); 

    return 0;
}
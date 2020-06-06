#include "layer.h"

/* The sigmoid function and derivative. */
double sigmoid(double x)
{
  return 1.0 / (1.0 + exp(-x));
  /* 1 MARK */
}

double sigmoidprime(double x)
{
  return x*(1 - x);
}

/* Creates a single layer. */
layer_t *layer_create()
{
  size_t size = sizeof(layer_t);
  layer_t *allocated = calloc(1, size);
  if (allocated == NULL) {
    return NULL;
  }
  return allocated;
  /* 4 MARKS */
}

bool layer_init(layer_t *layer, int num_outputs, layer_t *prev) {
  assert (layer != NULL);
  assert (num_outputs > 0);
  layer->num_outputs = num_outputs;
  layer->prev = prev;
  layer->outputs = calloc(num_outputs, sizeof(double));
  if (layer->outputs == NULL) {
    layer_free(layer);
    return true;
  }
  
  int num_inputs;
  if (prev != NULL) {
    num_inputs = prev->num_outputs;
  } else {
    num_inputs = 0;
  }
  layer->num_inputs = num_inputs;
  
  layer->weights = malloc(num_inputs * sizeof(double *));
  if (layer->weights == NULL) {
    layer_free(layer);
    return true;
  }

  for (int i = 0; i < num_inputs; i++) {
    layer->weights[i] = malloc(num_outputs * sizeof(double));
    if(layer->weights[i] == NULL) {
      layer_free(layer);
      return true;
    }
    for (int j = 0; j < num_outputs; j++) {
      layer->weights[i][j] = ANN_RANDOM();
    }
  }
  
  layer->biases = calloc(num_outputs, sizeof(double));
  if (layer->biases == NULL) {
    layer_free(layer);
    return true;
  }
  layer->deltas = calloc(num_outputs, sizeof(double));
  if (layer->deltas == NULL) {
    layer_free(layer);
    return true;
  }
  return false;
    
}

/* Frees a given layer. */
void layer_free(layer_t *layer) {
  assert(layer != NULL);
  for (int i = 0; i < layer->num_inputs; i++) {
    free((layer->weights)[i]);
  }
  free(layer->weights);
  free(layer->outputs);
  free(layer->biases);
  free(layer->deltas);
  free(layer);

  /* 2 MARKS */
}

/* Computes the outputs of the current layer. */
void layer_compute_outputs(layer_t const *layer) {
  assert(layer != NULL);
  for (int j = 0; j < layer->num_inputs; j++) {
    int sum = (layer->biases)[j];
    for (int i = 0; i < layer->num_outputs; i++) {
      sum += (layer->weights)[i][j] * (layer->prev->outputs)[i];
    }
    layer->outputs[j] = sigmoid(sum);
  }
  
  /* objective: compute layer->outputs */

  /* 3 MARKS */
}

/* Computes the delta errors for this layer. */
void layer_compute_deltas(layer_t const *layer)
{
  assert(layer != NULL);
  assert(layer->next != NULL);
  for (int i < 0; i < layer->num_inputs; i++){
    
  
  /* objective: compute layer->deltas */

  /* 2 MARKS */
}

/* Updates weights and biases according to the delta errors given learning rate. */
void layer_update(layer_t const *layer, double l_rate)
{
  /**** PART 1 - QUESTION 7 ****/
  /* objective: update layer->weights and layer->biases */

  /* 1 MARK */
}













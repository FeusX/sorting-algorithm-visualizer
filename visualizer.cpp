#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <vector>
using namespace std;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

void drawState(const vector<int>& vec, SDL_Renderer* renderer, int highlight_1, int highlight_2, int max_value, int stripe_width);
void selectionSort(vector<int>& vec, SDL_Renderer* renderer, int max_value, int stripe_width);
void bubbleSort(vector <int>& vec, SDL_Renderer* renderer, int max_value, int stripe_width);

int main()
{

if (SDL_Init(SDL_INIT_VIDEO) < 0) 
{
  cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
  return 1;
}
  int num_elements, range_start, range_end;
  cout << "Enter number of elements to sort: ";
  cin >> num_elements;

  cout << "Enter the range start: ";
  cin >> range_start;

  cout << "Enter the range end: ";
  cin >> range_end;

  if(range_end < range_start)
    swap(range_end, range_start);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dist(range_start, range_end);

  vector<int> vec;
  for(int i = 0; i < num_elements; ++i)
    vec.push_back(dist(gen));

  /*SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);*/

  int stripe_width = WINDOW_WIDTH / num_elements;

  uint8_t algorithm_number;
  cout << "0-Bubble Sort, 1-Selection Sort" << endl;
  cout << "Enter the algorithm that you want to visualize: ";
  cin >> algorithm_number;

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

  switch (algorithm_number)
  {
    case 0:
      bubbleSort(vec, renderer, range_end, stripe_width);
      break;
    case 1:
      selectionSort(vec, renderer, range_end, stripe_width);
      break;
    default:
      break;
  }

  SDL_Delay(2000);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

void drawState(const vector<int>& vec, SDL_Renderer* renderer, int highlight_1, int highlight_2, int max_value, int stripe_width)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  for(int i = 0; i < vec.size(); i++)
  {
    if(i == highlight_1)
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else if(i == highlight_2)
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    else
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int scaled_height = (static_cast<float>(vec[i]) / max_value) * WINDOW_HEIGHT;
    int x = i * stripe_width;
    SDL_Rect bar = { x, WINDOW_HEIGHT - scaled_height, stripe_width, scaled_height };
    SDL_RenderFillRect(renderer, &bar);
  }

  SDL_RenderPresent(renderer);
}

void selectionSort(vector<int>& vec, SDL_Renderer* renderer, int max_value, int stripe_width)
{
  for(int i = 0; i < vec.size(); i++)
  {
    int min_index = i;
    for(int j = i + 1; j < vec.size(); j++)
    {
      if(vec[j] < vec[min_index])
        min_index = j;
    }

    if(min_index != i)
      swap(vec[i], vec[min_index]);

    drawState(vec, renderer, i, min_index, max_value, stripe_width);
    SDL_Delay(10);
  }
}

void bubbleSort(vector <int>& vec, SDL_Renderer* renderer, int max_value, int stripe_width)
{
  bool swapped;
  int i = vec.size();
  do
  {
    swapped = false;
    for(int j = 0; j < vec.size() - 1; j++)
    {
      if(vec[j] > vec[j + 1])
      {
        swap(vec[j], vec[j + 1]);
        swapped = true;
      }
      drawState(vec, renderer, j, j + 1, max_value, stripe_width);
      SDL_Delay(10);
    }
    i--;
  }while(swapped);  
} 

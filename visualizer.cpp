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
void siftDown(vector<int>& vec, int start, int end);
void heapSort(vector<int>& vec, SDL_Renderer* renderer, int max_value, int stripe_width);

int main()
{
  SDL_Init(SDL_INIT_VIDEO);

  int num_elements, range_start, range_end;

  cout << "Enter number of elements to sort: ";
  cin >> num_elements;

  if(num_elements > 1024)
    cout << "[WARNING] More than 1024 elements might not visualized as intended." << endl;
  else if(num_elements < 2)
  {
    cout << "[ERROR] Element count can't be this low" << endl;
    return 1;
  }

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

  int stripe_width = WINDOW_WIDTH / num_elements;

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

  //selectionSort(vec, renderer, range_end, stripe_width);
  //bubbleSort(vec, renderer, range_end, stripe_width);
  heapSort(vec, renderer, range_end, stripe_width);

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

void heapSort(vector<int>& vec, SDL_Renderer* renderer, int max_value, int stripe_width)
{
  int size = vec.size();
  for(int i = size / 2 - 1; i >= 0; --i)
  {siftDown(vec, i, size);}

  for(int end = vec.size() - 1; end > 0; --end)
  {
    swap(vec[0], vec[end]);
    siftDown(vec, 0, end);
    drawState(vec, renderer, 0, end, max_value, stripe_width);
    SDL_Delay(10);
  }
} 

void siftDown(vector<int>& vec, int start, int end)
{
  int root = start;

  while(root * 2 + 1 < end)
  {
    int child = root * 2 + 1;
    int swap_idx = root;

    if(vec[swap_idx] < vec[child])
      swap_idx = child;

    if(child + 1 < end && vec[swap_idx] < vec[child + 1])
      swap_idx = child + 1;

    if(swap_idx == root)
      return;
    else
    {
      swap(vec[root], vec[swap_idx]);
      root = swap_idx;
    }
  }
}

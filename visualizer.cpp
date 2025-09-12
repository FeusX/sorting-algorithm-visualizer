#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <ranges>
#include <algorithm>
#include <climits>
using namespace std;

void drawState(vector<int>& vec, SDL_Renderer* renderer, uint16_t red, uint16_t blue, int range_end);
void selectionSort(vector<int>& vec, SDL_Renderer* renderer, int range_end);

int main()
{
  int range_end = 99;
  int range_start = 1;
  random_device rd;
  uniform_int_distribution d(range_start, range_end);
  vector<int> vec;

  /*cout << "Enter the range start: ";
  cin >> range_start;
  cout << "Enter the range end: ";
  cin >> range_end;*/

  if(range_end < range_start)
  {
    swap(range_end, range_start);
  }
  
  for(int i = 0; i < range_end; i++)
  {
    vec.push_back(d(rd));
  }

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_CreateWindowAndRenderer(100*10, 100*10, 0, &window, &renderer);
  SDL_RenderSetScale(renderer, 10, 10);

  selectionSort(vec, renderer, range_end);

  return 0;
}


void drawState(vector<int>& vec, SDL_Renderer* renderer, uint16_t red, uint16_t blue, int range_end)
{
  int index = 0;
  for(int i : vec)
  {
    if(index == red)
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else if(index == blue)
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    else
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_RenderDrawLine(renderer, index, range_end, index, i);
    index += 1;
  }
}

void selectionSort(vector<int>& vec, SDL_Renderer* renderer, int range_end)
{
  for(uint16_t i = 0; i < vec.size(); i++)
  {
    uint16_t min_index = i;
    
    for(uint16_t j = i + 1; j < vec.size(); j++)
    {
      if(vec[j] < vec[min_index])
        min_index = j;
     
    }
    if(min_index != i) swap(vec[i], vec[min_index]);
     
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    drawState(vec, renderer, i, min_index, range_end);  
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
  }
}

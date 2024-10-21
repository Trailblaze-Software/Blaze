#include "utilities/progress_tracker.hpp"

void run_loop(ProgressTracker tracker) {
  for (int i = 0; i < 10; i++) {
    ProgressTracker trackerA = tracker.subtracker(i / 10.0, (i + 1) / 10.0);
  }
}

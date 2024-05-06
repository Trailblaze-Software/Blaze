import os
import shutil
from pathlib import Path

Path("flat").mkdir(parents=True, exist_ok=True)
for folder in os.walk("out"):
    # if filename is final_img.tif move and rename in flat
    for t in ["final_img.tif", "ground_intensity.tif", "slope.tif"]:
        f = Path("flat") / t
        f.mkdir(parents=True, exist_ok=True)
        for filename in folder[2]:
            if filename == t:
                shutil.copy(
                    os.path.join(folder[0], filename),
                    os.path.join(f, folder[0].split("/")[-1] + ".tif"),
                )

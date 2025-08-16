import random

NUM_FILES = 5
NUM_INTEGERS = 500_000  # quantidade de inteiros por arquivo
MIN_VALUE = 0
MAX_VALUE = 1_000_000

for i in range(1, NUM_FILES + 1):
    filename = f"inputs/arq{i}.dat"
    print(f"Generating {filename} ...")
    with open(filename, "w") as f:
        for _ in range(NUM_INTEGERS):
            f.write(f"{random.randint(MIN_VALUE, MAX_VALUE)}\n")

print("All files generated successfully!")
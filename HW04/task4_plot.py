import csv
import re
import sys
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def read_timings(csv_path):
    timings = {"static": [], "dynamic": [], "guided": []}
    with open(csv_path, newline="") as f:
        reader = csv.reader(f)
        for row in reader:
            if not row:
                continue
            policy, threads, time_str = row

            match = re.search(r"([0-9]+(?:\.[0-9]+)?)", str(time_str))
            if not match:
                continue
            value = float(match.group(1))

            timings.setdefault(policy, []).append((int(threads), value))
    for policy in timings:
        timings[policy].sort(key=lambda x: x[0])
    return timings


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <timings.csv> <output.pdf>")
        raise SystemExit(1)

    csv_path = Path(sys.argv[1])
    out_path = Path(sys.argv[2])

    timings = read_timings(csv_path)

    fig, axes = plt.subplots(1, 3, figsize=(15, 5), constrained_layout=True)
    fig.suptitle("OpenMP scheduling comparison for N-body simulation")

    for ax, policy in zip(axes, ["static", "dynamic", "guided"]):
        data = timings.get(policy, [])
        if not data:
            ax.set_visible(False)
            continue

        threads = [t for t, _ in data]
        times = [t for _, t in data]

        ax.plot(threads, times, marker="o", linewidth=2)
        ax.set_title(policy)
        ax.set_xlabel("Num threads")
        ax.set_ylabel("Time (ms)")
        ax.grid(True, linestyle="--", alpha=0.5)
        ax.set_xlim(0.5, max(threads) + 0.5)

    fig.savefig(out_path, format="pdf")
    print(f"Saved plot to {out_path}")


if __name__ == "__main__":
    main()

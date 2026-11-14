#!/usr/bin/env python3

import re
import subprocess
import sys
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def replace_block_size(file_path: Path, threads_per_block: int) -> str:
    text = file_path.read_text(encoding="utf-8")
    pattern = r"int threadsPerBlock =\s*\d+;"
    replacement = f"int threadsPerBlock = {threads_per_block};"
    new_text, count = re.subn(pattern, replacement, text, count=1)
    if count != 1:
        raise RuntimeError("Could not find the threadsPerBlock assignment in task3.cu")
    file_path.write_text(new_text, encoding="utf-8")
    return text


def compile_and_run(hw_dir: Path, block_size: int, n: int):
    task3_path = hw_dir / "task3.cu"
    original = replace_block_size(task3_path, block_size)
    try:
        subprocess.run(
            [
                "nvcc",
                "task3.cu",
                "vscale.cu",
                "-Xcompiler",
                "-O3",
                "-Xcompiler",
                "-Wall",
                "-Xptxas",
                "-O3",
                "-std=c++17",
                "-o",
                "task3",
            ],
            cwd=hw_dir,
            check=True,
            capture_output=True,
            text=True,
        )

        completed = subprocess.run(
            [str(hw_dir / "task3"), str(n)],
            cwd=hw_dir,
            check=True,
            capture_output=True,
            text=True,
        )
        first_line = completed.stdout.strip().splitlines()[0]
        return float(first_line)
    finally:
        task3_path.write_text(original, encoding="utf-8")


def main():
    hw_dir = Path(__file__).resolve().parent
    block_sizes = [16, 512]
    powers = list(range(10, 30))

    data = {block_size: [] for block_size in block_sizes}

    for block_size in block_sizes:
        for exponent in powers:
            n = 2 ** exponent
            time_ms = compile_and_run(hw_dir, block_size, n)
            data[block_size].append((n, time_ms))

    for block_size in block_sizes:
        out_path = hw_dir / f"task3_{block_size}.dat"
        with out_path.open("w", encoding="utf-8") as f:
            for n, t in data[block_size]:
                f.write(f"{n} {t}\n")

    plt.figure(figsize=(8, 5))
    for block_size in block_sizes:
        n_vals = [n for n, _ in data[block_size]]
        time_vals = [t for _, t in data[block_size]]
        label = f"{block_size} threads/block"
        plt.plot(n_vals, time_vals, marker="o", label=label, linewidth=2)

    plt.xscale("log", base=2)
    plt.yscale("log")
    plt.xlabel("n")
    plt.ylabel("Time (ms)")
    plt.title("vscale scaling comparison")
    plt.grid(True, which="both", linestyle="--", alpha=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(hw_dir / "task3.pdf")
    print("Saved task3.pdf")


if __name__ == "__main__":
    main()

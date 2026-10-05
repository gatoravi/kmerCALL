# kmerCALL

An alignment-light, **k-mer based scan for de novo mutations** in
parent-offspring trios (2013 prototype).

## Idea

A de novo mutation creates DNA sequence in the child that neither parent
carries. Instead of calling genotypes position by position, kmerCALL looks for
that signal directly in the reads:

1. Slide a window along a region of the genome.
2. Pull the reads in that window from the child's, mother's and father's BAM
   files.
3. Count 10-mers in each sample's reads with
   [Jellyfish](https://github.com/gmarcais/Jellyfish).
4. For every k-mer seen in all three samples with enough total coverage,
   compute a child-excess score: the child's share of the k-mer's reads minus
   the mother's and father's shares.
5. Summarise each window as the mean of the 10 highest scores minus the mean
   of the 10 lowest. Windows with an unusually large spread are candidate
   regions for a de novo event.

Working on k-mers instead of aligned bases makes the approach less sensitive
to alignment artifacts around indels and complex variants.

## Build

Depends on samtools 0.1.18 (`libbam`), Jellyfish 1.1.x and zlib.
`src/CMakeLists.txt` currently hard-codes the paths to those libraries, so
edit them to match your system first.

```bash
cd src
mkdir build && cd build
cmake ..
make
```

The `jellyfish` executable must also be on your `PATH`, because kmerCALL calls
`jellyfish count` and `jellyfish dump` for each window.

## Usage

```bash
kmerCall --child_bam child.bam --mom_bam mother.bam --dad_bam father.bam \
         --chr 1 --start 1000000 --end 2000000 --window 1000 \
         --output window_stats.tsv
```

## Output

`--output` (and standard output) gets one line per window:

```
chr    window_start    window_statistic
```

For each window, a `window_<start>.txt` file with the per-k-mer counts and
scores is also written to the working directory.

## Status

This is a proof-of-concept from Don Conrad's lab at Washington University and
is not maintained. For production de novo calling see
[DeNovoGear](https://github.com/ultimatesource/denovogear).

## License

GPL-3.0 (see the source file headers).

<h1 align="left">fileusage</h1>

###

<p align="left">A Windows console application that lists file usage by grouping files based on their extensions. It counts the total number of files and calculates their cumulative sizes.</p>

###

<h2 align="left">Features</h2>

###

<ul>
  <li>Lists files in a directory and groups them by their file extensions.</li>
  <li>Displays the total number of files per extension.</li>
  <li>Calculates the cumulative size of files for each extension.</li>
  <li>Simple, fast, and lightweight console-based interface.</li>
</ul>

###

<h2 align="left">Usage</h2>

###

<pre style="font-family: Consolas, monospace; font-size: 14px; background-color: #eee; padding: 15px; border: 1px solid #ccc; border-radius: 5px; white-space: pre; color: #333;">
        Usage: fileusage [--help] [-hdrsv(x regularexpression)] [folder]
        switches:
                h       help
                d       reverse the order of listing
                r       suppress recursion
                s       sort by file sizes
                v       verbose
                b       benchmark
                x       filter with a regular expression

        folder
                starting folder or current folder if not specified
</pre>

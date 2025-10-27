#!/usr/bin/env python3
# tools/comment_compat.py
# Usage: python3 tools/comment_compat.py
# Makes .bak backups of modified files.

import sys
import os
from pathlib import Path

ROOT = Path('.').resolve()

def process_file(path: Path):
    text = path.read_text(encoding='utf-8', errors='replace').splitlines()
    changed = False
    i = 0
    out = text[:]  # we'll modify this as list of lines
    while i < len(text):
        line = text[i]
        if 'COMPAT_SYSCALL_DEFINE' in line:
            # found the macro start
            start = i
            # find the opening brace '{' and then match braces until balanced
            j = i
            found_open = False
            brace_count = 0
            while j < len(text):
                l = text[j]
                # count braces in this line (naive but good for C function bodies)
                # ignore braces in comment markers? we assume normal code
                brace_count += l.count('{')
                brace_count -= l.count('}')
                if l.count('{') > 0:
                    found_open = True
                # if we've seen the opening and brace_count is 0 again, function ended
                if found_open and brace_count == 0:
                    end = j
                    break
                j += 1
            else:
                # reached EOF without balancing braces — bail out for safety
                print(f"WARNING: unmatched braces in {path} starting at line {start+1}. Skipping.")
                i = j + 1
                continue

            # comment lines from start..end inclusive in 'out'
            for k in range(start, end+1):
                if not out[k].lstrip().startswith('//'):
                    out[k] = '//' + out[k]
                    changed = True

            # advance i beyond end
            i = end + 1
        else:
            i += 1

    if changed:
        bak = path.with_suffix(path.suffix + '.bak')
        if not bak.exists():
            path.rename(bak)            # move original to .bak
            # write modified content to original path
            path.write_text('\n'.join(out) + '\n', encoding='utf-8')
            print(f"Patched: {path} (backup -> {bak})")
        else:
            # If .bak exists, don't overwrite it; write .mod and notify
            mod = path.with_suffix(path.suffix + '.mod')
            path.write_text('\n'.join(out) + '\n', encoding='utf-8')
            print(f"Patched (but {bak} already exists): {path} (wrote .mod)")
    return changed

def main():
    # search .c files only (skip third-party directories if you want)
    c_files = list(ROOT.rglob('*.c'))
    # optional: limit to kernel source directories by pattern (ipc/, fs/, mm/, net/, etc.)
    # c_files = [p for p in c_files if any(part in p.parts for part in ('ipc','fs','mm','kernel','net'))]

    modified = 0
    for f in c_files:
        # skip build directories
        if any(part in ('.git', 'out', 'build', 'tools') for part in f.parts):
            continue
        try:
            if process_file(f):
                modified += 1
        except Exception as e:
            print(f"ERROR processing {f}: {e}")

    print(f"Done. Modified {modified} files.")

if __name__ == '__main__':
    main()

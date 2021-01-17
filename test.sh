#!/usr/bin/env bash

set -ex

./hack test/actual/empty.asm
diff test/expect/empty.hack test/actual/empty.hack

./hack test/actual/commanda.asm
diff test/expect/commanda.hack test/actual/commanda.hack

./hack test/actual/commandc.asm
diff test/expect/commandc.hack test/actual/commandc.hack

./hack test/actual/space.asm
diff test/expect/space.hack test/actual/space.hack

./hack test/actual/comment.asm
diff test/expect/comment.hack test/actual/comment.hack

./hack test/actual/lf.asm
diff test/expect/lf.hack test/actual/lf.hack

./hack test/actual/program1.asm
diff test/expect/program1.hack test/actual/program1.hack

./hack test/actual/program2.zzzzz
diff test/expect/program2.hack test/actual/program2.hack

./hack test/actual/program3
diff test/expect/program3.hack test/actual/program3.hack

cat test/actual/program1.asm | ./hack > test/actual/program1.stdout.hack
diff test/expect/program3.hack test/actual/program1.stdout.hack

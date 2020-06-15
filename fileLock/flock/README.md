Write two programs and try to lock the same file
1. Shared lock.
2. Exclusive lock.
Try to use two locking methods: flock and fcntl

if you run exlock first then run the shlock ,the shlock.c will not lock success,until the exlock release.

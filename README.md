```
                   _   ___  ___  
  _ __   ___  _ __| |_( _ )/ _ \ 
 | '_ \ / _ \| '__| __/ _ \ (_) |
 | |_) | (_) | |  | || (_) \__, |
 | .__/ \___/|_|   \__\___/  /_/ 
 |_|
```

part of ae2f::Preproc  
tools to generate C89 headers.

sometimes newer c headers don't respect c89, yet some features are interchangable.  
some patterns i noticed will be fixed here.

these should be work on VERY SIMPLE headers enough to be converted.

# requirements
- stdio.h
- git
- cmake
- make
- compiler

## llong
> change `long long` type into another we want as argument.

## cenum
> remove comma on last enum definition.

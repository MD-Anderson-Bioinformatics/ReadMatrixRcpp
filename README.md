# ReadMatrixRcpp

This is for educational and research purposes only. 

http://bioinformatics.mdanderson.org

The goal of the Gene Survey project is to take TCGA Standardized Data and make gene level cross-disease and sometimes cross platform comparisons and evaluations simpler to perform, as these represent common questions asked of researchers and analysts. That is, we are answering a common question: how does gene XYZ act across disease types?

This is the R package used to quickly read very large "platform" level matrices. (Some of the matrices are so large reading them in R is excessively slow and they are large enough to overflow the size support in rJava. Some will require machines in excess of 40GB of free memory.) If you do not wish to use platform level matrices (this is all TCGA data for a particular gene across all platforms supported by GeneSurvey), then this R package may be safely omitted and you can ignore the suggested package does not exist warning messages from R.

# General Prerequisites

If the wrong version of GCC is used, you can get deceptive errors, such as a missing symbol making an so file unloadable.
The R package Rcpp must be installed using the same compiler version as used for ReadMatrixRcpp.

# Linux Prerequisites

The ReadMatrixRcpp package under Linux (Debian/Ubuntu) requires the Linux DEB packages: libssl-dev, libxml2-dev, libcurl4-openssl-dev, lzma, lzma-dev, and liblzma-dev.

The local versions for modules are:

gcc/4.9.0
xz/5.2.2
pcre/8.38
curl/7.37.1
zlib/1.2.8
bzip2/1.0.6
autoconf/2.69
automake/1.15
m4/1.4.17
R/3.3.0

Other distributions will have similar packages. The R package install of "devtools" described under R Prerequisites indicate what Linux installs are missing.

# Windows and OSX Prerequisites

Windows and OSX installations will also need any extras needed for compiling R packages.
Running under Windows and OSX enviroments is neither tested nor supported, but is theoretically possible.

# R Prerequisites

The devtools and Rcpp packages need to be installed.

```r
install.packages("devtools", dependencies=TRUE)
install.packages("Rcpp", dependencies=TRUE, type="source")
```

# Linux Install

```r
devtools::install_github("MD-Anderson-Bioinformatics/GeneSurvey", args="--preclean")
```

# Windows Install

If you are setup for multi-architecture compiles in Windows, you can remove the args parameter.
```r
devtools::install_github("MD-Anderson-Bioinformatics/GeneSurvey", args="--no-multiarch --preclean")
```

# Other Projects

The https://github.com/MD-Anderson-Bioinformatics/GSAccess and https://github.com/MD-Anderson-Bioinformatics/GeneSurvey projects utilize this package.

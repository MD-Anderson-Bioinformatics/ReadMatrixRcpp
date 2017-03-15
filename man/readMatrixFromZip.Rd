\name{readMatrixFromZip}
\alias{readMatrixFromZip}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{readMatrixFromZip}
\description{
Read a matrix with column and row headers using CPP.
}
\usage{
readMatrixFromZip(theZipFile, theMatrixFile)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{theZipFile}{the full path to the ZIP file containing the TSV to read}
  \item{theMatrixFile}{the full path within the ZIP file to the TSV to read}
}
\details{
Read a matrix with column and row headers using CPP.
Column header line should start with a tab.
This is used for larger files where the rJava interface was having memory issues.
}
\value{
Return a numeric matrix with samples for columns and genes for rows (or whatever was in the original file).
Or NULL is the file is not found.
}
\references{}
\author{}
\note{}
\seealso{}
\examples{
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }% use one of  RShowDoc("KEYWORDS")
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line

#!/usr/bin/perl
eval 'exec /usr/bin/perl -S $0 ${1+"$@"}'
	if $running_under_some_shell;

while ($ARGV[0] =~ /^-/) {
	$_ = shift;
	last if /^--/;
	if (/^-n/) {
	$nflag++;
	next;
	}
	die "I don't recognize this switch: $_\\n";
}
$printit++ unless $nflag;

$\ = "\n";	# automatically add newline on print

while (<>) {
	chop;
	s/a"/�/g;
	s/A"/�/g;
	s/o"/�/g;
	s/O"/�/g;
	s/u"/�/g;
	s/U"/�/g;
	s/sS/�/g;
	print if $printit;
}

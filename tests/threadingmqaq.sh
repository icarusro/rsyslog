# test many concurrent tcp connections
# we send 100,000 messages in the hopes that his puts at least a little bit
# of pressure on the threading subsystem. To really prove it, we would need to
# push messages for several minutes, but that takes too long during the 
# automatted tests (hint: do this manually after suspect changes). Thankfully,
# in practice many threading bugs result in an abort rather quickly and these
# should be covered by this test here.
# rgerhards, 2009-06-26
echo \[threadingmqaq.sh\]: main/action queue concurrency
source $srcdir/diag.sh init
source $srcdir/diag.sh startup threadingmqaq.conf
#source $srcdir/diag.sh tcpflood 127.0.0.1 13514 2 100000
#source $srcdir/diag.sh shutdown-when-empty # shut down rsyslogd when done processing messages
source $srcdir/diag.sh injectmsg 0 100000
source $srcdir/diag.sh shutdown-when-empty # shut down rsyslogd when done processing messages
source $srcdir/diag.sh wait-shutdown
source $srcdir/diag.sh seq-check 0 99999
source $srcdir/diag.sh exit

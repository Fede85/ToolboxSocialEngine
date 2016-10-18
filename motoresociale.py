import tweepy
import json, sys, time

consumer_key = ""
consumer_secret = ""
access_key = ""
access_secret = ""

#sys.path.insert(0, '/usr/lib/python2.7/bridge/')
#from bridgeclient import BridgeClient as bridgeclient

#client = bridgeclient()
#searchKeywords = client.getall()

class CustomStreamListener(tweepy.StreamListener):
	def on_status(self, status):
		msg = status.text.encode('ascii', errors='ignore')
		#global 	searchKeywords	
		#searchKeywords = client.getall()
		#client.mailbox(msg)
	        print msg
		#print '\n\n'

	def on_error(self, status_code):
	        print >> sys.stderr, 'Encountered error with status code:', status_code
	        return True # Don't kill the stream

	def on_timeout(self):
	        print >> sys.stderr, 'Timeout...'
	        return True # it's ok...

	def on_limit(self, track):
		print "reached limit"
		return True

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_key, access_secret)
api = tweepy.API(auth)


stream = tweepy.streaming.Stream(auth, CustomStreamListener())
# we really feel the need to follow a twitter stream
#keyStorageContent = client.getall()
#keywordsToFollow = [unicode(i) for i in keyStorageContent.values()] # to encode or not to encode?
keywordsToFollow = ['obama', 'boobs']
stream.filter(track=keywordsToFollow)

'''
while True:
	print 'disconnect'
	stream.disconnect()
	keyStorageContent = client.getall()
	keywordsToFollow = [unicode(i) for i in keyStorageContent.values()] # to encode or not to encode?
	if keywordsToFollow == '':
		print 'no keywords dude!'
	else:
		print keywordsToFollow
		print '-----------------------------------------------\n\n\n\n'
		stream.filter(track=keywordsToFollow, async=True)
	print 'going to sleep'
	time.sleep(100);
'''

import os
import atexit
import pydantic
from time import time as now
from typing import Callable, Any
from watchdog.observers import Observer
from watchdog.events import PatternMatchingEventHandler

from ..Source import Source



onChange_type = Callable[[], Any]


@pydantic.validate_arguments(config={'arbitrary_types_allowed': True})
def getObserverStopper(o: Observer):

	def stop():
		o.stop()
	
	return stop


class FileEventsHandler(PatternMatchingEventHandler):

	@pydantic.validate_arguments
	def __init__(self, onChange: onChange_type, *args, **kwargs):

		super().__init__(*args, **kwargs)

		self._onChange = onChange
		self._last_triggered_time = 0


	def on_modified(self, _):

		the_time = now()

		if the_time - self._last_triggered_time >= 1:
			self._onChange()
			self._last_triggered_time = the_time


@pydantic.validate_arguments
def watchFile(path: str, onChange: onChange_type):

	handler = FileEventsHandler(onChange, patterns=[path])

	observer = Observer()
	observer.schedule(handler, path=os.path.dirname(path) or '.', recursive=False)

	stopObserver = getObserverStopper(observer)
	atexit.register(stopObserver)

	observer.start()

	return stopObserver


class FileSource(Source):

	@pydantic.validate_arguments
	def __init__(self, path: str, watch: bool = False):
		self.path = path
		self._stopObserver = None
		self._watch = watch

	def get(self):
		with open(self.path) as f:
			return f.read()

	def onChange_setter(self, value):
		self.stopWatch()
		self.startWatch(value)

	def startWatch(self, onChange: onChange_type):
		if self._watch:
			self._stopObserver = watchFile(self.path, onChange)

	def stopWatch(self):
		if self._stopObserver:
			self._stopObserver()
			self._stopObserver = None

	def clean(self):
		self.stopWatch()

	@property
	def id(self):
		return self.path
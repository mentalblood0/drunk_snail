import functools
from sharpener_lite import units



class OutputIsRun:

	@property
	def output(self):
		return self.run()


class WithOutputMetrics(OutputIsRun):

	@property
	def metric_size(self):
		return len(self.output) * units.byte

	@property
	def metric_speed(self):
		return (self.metric_size / self.metric_mean_time).to(units.megabyte / units.second)


class WithTableArgs:

	@functools.cached_property
	def args(self):
		return {
			"Row": [
				{
					"cell": [
						str(x)
						for x in range(self.config.kwargs['width'])
					]
				}
				for y in range(self.config.kwargs['height'])
			]
		}
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
						str(x + y * self.config.kwargs['width'])
						for x in range(self.config.kwargs['width'])
					]
				}
				for y in range(self.config.kwargs['height'])
			]
		}


class WithName:

	@property
	def metric_name_markdown(self):
		if self.link is None:
			return self.name
		else:
			return f'[{self.name}]({self.link})'
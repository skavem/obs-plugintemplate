#include <obs-module.h>
#include <util/base.h>

struct test_filter {
	obs_source_t *source;

  uint64_t focus_level;
};

static const char *filter_getname(void *unused)
{
	UNUSED_PARAMETER(unused);
	return "Test";
}

static void *filter_create(obs_data_t *settings, obs_source_t *source)
{
	struct test_filter *tf = bzalloc(sizeof(struct test_filter));

	obs_enter_graphics();

	tf->source = source;

	obs_leave_graphics();

	UNUSED_PARAMETER(settings);
	return tf;
}

static void filter_destroy(void *data)
{
	struct test_filter *tf = data;

	if (tf) {
		obs_enter_graphics();

		bfree(tf);

		obs_leave_graphics();
	}
}

static struct obs_source_frame * 
filter_render(void *data, struct obs_source_frame *frame) {
	struct test_filter *tf = data;

  char str[20];
  snprintf(str, sizeof(str), "H: %u", frame->height);
  blog(300, str);

  return frame;
}

struct obs_source_info my_source {
  .id           = "my_source",
  .type         = OBS_SOURCE_TYPE_FILTER,
  .output_flags = OBS_SOURCE_VIDEO | OBS_SOURCE_ASYNC,
  .get_name     = filter_getname,
  .create       = filter_create,
  .destroy      = filter_destroy,
  .filter_video = filter_render,
};
#include "catch.hpp"
#include "lib.hpp"

TEST_CASE("config loads") {
  Config cfg{};
  cfg.open();
  CHECK(cfg.buffer_path == "./clipboard_data");

  std::vector<uint16_t> true_keys = {125, 29, 42, 56, 46, 47, 45};
  std::vector<uint16_t> true_masks = {1, 2, 4, 8, 16, 32, 64};
  for (size_t i = 0; i < true_masks.size(); ++i)
    CHECK(true_masks[i] == cfg.key_masks[true_keys[i]]);
  CHECK(cfg.max_entries == 10);
  CHECK(cfg.multisave == true);
}

TEST_CASE("config saves") {
  Config cfg, cfg1;
  cfg.open();
  cfg.multisave = false;
  cfg.save();
  cfg1.open();
  CHECK(cfg1.multisave == false);
  cfg1.multisave = true;
  cfg1.save();
}

TEST_CASE("clipboard opens & saves") {
  Clipboard cld, cld1;
  cld.open("./test_data");
  REQUIRE(cld.contents.size() == 2);
  CHECK(cld[0] == "first copied line");
  CHECK(cld[1] == "second one");
  cld.contents.push_back("123");
  cld.save("./test_data");
  cld1.open("./test_data");
  REQUIRE(cld1.contents.size() == 3);
  CHECK(cld1[0] == "first copied line");
  CHECK(cld1[1] == "second one");
  CHECK(cld1[2] == "123");
  cld1.contents.pop_back();
  cld1.save("./test_data");
}

TEST_CASE("preprocessing string") {
  std::string a = "abcdefghijklmnopqrstuvwxyz\n"
                  "abcdefghijklmnopqrstuvwxyz\n"
                  "abcdefghijklmnopqrstuvwxyz\n"
                  "abcdefghijklmnopqrstuvwxyz\n";
  auto b = process_string_to_view(a);
  CHECK(b == "abcdefghijklmnopqrstuvwxyz{endl}abcdefghijklmnopqrstuvwxyz{endl}"
             "abcdefghijklmnop...");
}

TEST_CASE("check compare events") {
  uiohook::uiohook_event a, b;
  b.type = a.type = uiohook::event_type::EVENT_KEY_PRESSED;
  b.data.keyboard.keycode = a.data.keyboard.keycode = uiohook::VC_A;
  REQUIRE(a == b);
  b.data.keyboard.keycode = uiohook::VC_B;
  CHECK_FALSE(a == b);
  b.data.keyboard.keycode = uiohook::VC_A;
  b.type = uiohook::event_type::EVENT_KEY_RELEASED;
  CHECK_FALSE(a == b);
}
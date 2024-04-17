#include "client/image_processing/table_recognizer.h"

#include "client/image_processing/image_loader.h"
#include "gtest/gtest.h"

namespace imgp = table_recognizer::client::image_processing;

void AssertTablesEquality(imgp::Table& t1, imgp::Table& t2) {
  size_t t1_height = t1.getHeight();
  size_t t2_height = t2.getHeight();
  size_t t1_width = t1.getWidth();
  size_t t2_width = t2.getWidth();
  ASSERT_EQ(t1_height, t2_height);
  ASSERT_EQ(t1_width, t2_width);
  if (t1_height != t2_height || t1_width != t2_width) {
    return;
  }

  for (size_t y = 0; y < t1_height; y++) {
    for (size_t x = 0; x < t1_width; x++) {
      std::string a = t1.getCell(x, y);
      EXPECT_EQ(t1.getCell(x, y), t2.getCell(x, y));
    }
  }
}

TEST(TableRecognizerTest, NormalTable) {
  imgp::Table expected_table(19, 16);
  expected_table.setCell(1, 0, "М3О-214Б-22");
  expected_table.setCell(3, 0, "17.02");
  expected_table.setCell(0, 1, "1");
  expected_table.setCell(1, 1, "Алексеев Павел Михайлович");
  expected_table.setCell(3, 1, "+");
  // TODO: Fill the table

  imgp::Recognizer recognizer;
  cv::Mat image =
      imgp::LoadImage("../../client/test/tableRecognizerTestData/normal.jpg");
  imgp::Table table = recognizer.Recognize(image);

  AssertTablesEquality(expected_table, table);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

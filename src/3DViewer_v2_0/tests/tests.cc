#include <gtest/gtest.h>

#include "../model/3D_object.h"
#include "../model/parser.h"

double kEps = 1e-5;

TEST(Parser, none) {
  s21::Parser p;

  EXPECT_THROW(p.Parse("none.obj"), std::runtime_error);
}

TEST(Parser, invalid_vertex) {
  s21::Parser p;

  EXPECT_THROW(p.Parse("tests/models/invalid_vertex.obj"),
               std::invalid_argument);
}

TEST(Parser, parse) {
  s21::Parser p;
  auto obj = p.Parse("tests/models/test.obj");

  std::vector<double> v{-0.5, -0.5, -0.5, 0, 0, 0, 0.5, 0.5, 0.5};
  std::vector<int> f{0, 1, 1, 2, 2, 0};

  EXPECT_EQ(obj->Vertices(), v);
  EXPECT_EQ(obj->FaceIndices(), f);
}

TEST(Object, translation) {
  s21::Parser p;
  auto obj = p.Parse("tests/models/test.obj");

  obj->Translate(1.3, s21::X);
  std::vector<double> v{0.8, -0.5, -0.5, 1.3, 0, 0, 1.8, 0.5, 0.5};
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);

  obj->Translate(-0.2, s21::Y);
  v = {0.8, -0.7, -0.5, 1.3, -0.2, 0, 1.8, 0.3, 0.5};
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);

  obj->Translate(-8, s21::Z);
  v = {0.8, -0.7, -8.5, 1.3, -0.2, -8, 1.8, 0.3, -7.5};
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);
}

TEST(Object, rotation) {
  s21::Parser p;
  auto obj = p.Parse("tests/models/test.obj");

  obj->Rotate(2, s21::X);
  std::vector<double> v{-0.5, 0.662722, -0.246575, 0,       0,
                        0,    0.5,      -0.662722, 0.246575};
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);

  obj->Rotate(-1.3, s21::Y);
  v = {0.10384, 0.662722, -0.547738, 0, 0, 0, -0.10384, -0.662722, 0.547738};
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);

  obj->Rotate(0.6, s21::Z);
  v = {-0.288498, 0.605601, -0.547738, 0, 0, 0, 0.288498, -0.605601, 0.547738 };
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);
}

TEST(Object, Scale) {
  s21::Parser p;
  auto obj = p.Parse("tests/models/test.obj");

  obj->Scale(4.2);
  std::vector<double> v{-2.1, -2.1, -2.1, 0, 0, 0, 2.1, 2.1, 2.1};
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);

  obj->Scale(0.1);
  v = {-0.21, -0.21, -0.21, 0, 0, 0, 0.21, 0.21, 0.21};
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_NEAR(obj->Vertices()[i], v[i], kEps);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

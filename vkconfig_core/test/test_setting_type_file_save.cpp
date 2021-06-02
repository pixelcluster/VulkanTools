/*
 * Copyright (c) 2020-2021 Valve Corporation
 * Copyright (c) 2020-2021 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Authors:
 * - Christophe Riccio <christophe@lunarg.com>
 */

#include "../setting_filesystem.h"
#include "../layer.h"

#include <gtest/gtest.h>

static_assert(SettingMetaFileSave::TYPE == SETTING_SAVE_FILE, "Invalid type");

TEST(test_setting_type_file_save, meta_equal) {
    Layer layer;

    SettingMetaFileSave* meta0 = Instantiate<SettingMetaFileSave>(layer, "key");
    meta0->default_value = "valueA";
    SettingMetaFileSave* meta1 = Instantiate<SettingMetaFileSave>(layer, "key");
    meta1->default_value = "valueA";
    EXPECT_EQ(*meta0, *meta1);

    meta1->default_value = "valueB";
    EXPECT_NE(*meta0, *meta1);
}

TEST(test_setting_type_file_save, data_equal) {
    Layer layer;

    SettingMetaFileSave* meta = Instantiate<SettingMetaFileSave>(layer, "key");

    SettingDataFileSave* data0 = Instantiate<SettingDataFileSave>(meta);
    EXPECT_STREQ(meta->key.c_str(), data0->key.c_str());

    SettingDataFileSave* data1 = Instantiate<SettingDataFileSave>(meta);
    EXPECT_STREQ(meta->key.c_str(), data1->key.c_str());

    EXPECT_EQ(*data0, *data1);

    data0->value = "value";
    EXPECT_NE(*data0, *data1);

    data1->value = "value";
    EXPECT_EQ(*data0, *data1);
}
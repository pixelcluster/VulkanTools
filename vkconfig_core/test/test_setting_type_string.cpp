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

#include "../setting_string.h"
#include "../layer.h"

#include <gtest/gtest.h>

static_assert(SettingMetaString::TYPE == SETTING_STRING, "Invalid type");

TEST(test_setting_type_string, meta_equal) {
    Layer layer;

    SettingMetaString* meta0 = Instantiate<SettingMetaString>(layer, "key");
    meta0->default_value = "76";
    SettingMetaString* meta1 = Instantiate<SettingMetaString>(layer, "key");
    meta1->default_value = "76";
    EXPECT_EQ(*meta0, *meta1);

    meta1->default_value = "75";
    EXPECT_NE(*meta0, *meta1);
}

TEST(test_setting_type_string, data_equal) {
    Layer layer;

    SettingMetaString* meta = Instantiate<SettingMetaString>(layer, "key");

    SettingDataString* data0 = Instantiate<SettingDataString>(meta);
    EXPECT_STREQ(meta->key.c_str(), data0->key.c_str());

    SettingDataString* data1 = Instantiate<SettingDataString>(meta);
    EXPECT_STREQ(meta->key.c_str(), data1->key.c_str());

    EXPECT_EQ(*data0, *data1);

    data0->value = "76";
    EXPECT_NE(*data0, *data1);

    data1->value = "76";
    EXPECT_EQ(*data0, *data1);

    SettingMetaString* metaX = Instantiate<SettingMetaString>(layer, "keyX");
    SettingDataString* dataX = Instantiate<SettingDataString>(metaX);
    dataX->value = "76";

    EXPECT_NE(*data0, *dataX);
}

TEST(test_setting_type_string, is_supported_meta_default) {
    Layer layer;

    SettingMetaString* meta = Instantiate<SettingMetaString>(layer, "key");

    EXPECT_EQ(true, IsSupported(meta));
}

TEST(test_setting_type_string, is_supported_meta_null) {
    const SettingMeta* meta = nullptr;

    EXPECT_EQ(false, IsSupported(meta));
}

TEST(test_setting_type_string, is_supported_value_hidden) {
    Layer layer;

    SettingMetaString* meta = Instantiate<SettingMetaString>(layer, "key");
    meta->view = SETTING_VIEW_HIDDEN;

    EXPECT_EQ(false, IsSupported(meta));
}

TEST(test_setting_type_string, is_supported_value_platform) {
    Layer layer;

    SettingMetaString* meta = Instantiate<SettingMetaString>(layer, "key");
    meta->platform_flags = 0;

    EXPECT_EQ(false, IsSupported(meta));
}
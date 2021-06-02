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

#include "../setting_bool.h"
#include "../layer.h"

#include <gtest/gtest.h>

static_assert(SettingMetaBool::TYPE == SETTING_BOOL, "Invalid type");

TEST(test_setting_type_bool, meta_equal) {
    Layer layer;

    SettingMetaBool* meta0 = Instantiate<SettingMetaBool>(layer, "key");
    meta0->default_value = true;
    SettingMetaBool* meta1 = Instantiate<SettingMetaBool>(layer, "key");
    meta1->default_value = true;

    EXPECT_EQ(*meta0, *meta1);

    meta1->default_value = false;
    EXPECT_NE(*meta0, *meta1);
}

TEST(test_setting_type_bool, data_equal) {
    Layer layer;

    SettingMetaBool* meta = Instantiate<SettingMetaBool>(layer, "key");

    SettingDataBool* data0 = Instantiate<SettingDataBool>(meta);
    data0->value = true;
    EXPECT_STREQ(meta->key.c_str(), data0->key.c_str());

    SettingDataBool* data1 = Instantiate<SettingDataBool>(meta);
    data1->value = true;
    EXPECT_STREQ(meta->key.c_str(), data1->key.c_str());

    EXPECT_EQ(*data0, *data1);

    data1->value = false;
    EXPECT_NE(*data0, *data1);
}

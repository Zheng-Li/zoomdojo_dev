<div id="edit-tab-bck-view">
    <form method="POST" id="form-tabbbled-block">
        <div id="dialog" title="Select category">
            <div>
                <input type="radio" name="categ_radio" value="0" id="select-categ-radio-1" checked="checked" class="category-radios" />
                <label>Select category</label>
                <div class="clearfix"></div>
                <select id="select-category">
                    <?php foreach ($allCategories as $category): ?>
                        <option value="<?php print $category->id; ?>"><?php print $category->title; ?></option>
                    <?php endforeach; ?>
                </select>
            </div>
            <div class="new-section">
                <input type="radio" name="categ_radio" value="1" id="select-categ-radio-2" class="category-radios" />
                <label>Create category</label>
                <div class="clearfix"></div>
                <input type="text" name="new_cat_name" value="" id="new-categ-name" />
            </div>
        </div>

        <a href="#" class="button" id="add_tab">Add category</a>
         
        <div id="tabs">
            <ul>
                <?php foreach ($categories as $category): ?>
                    <li>
                        <a href="#tabs-<?php print $category->id; ?>"><?php print $category->title; ?></a>
                        <span class="ui-icon ui-icon-close" role="presentation">Remove Tab</span>
                    </li>
                <?php endforeach; ?>
            </ul>
            <?php foreach ($categories as $category): ?>
                <div id="tabs-<?php print $category->id; ?>">
                    <div class="add-item">
                        <a href="#" data-cid="<?php print $category->id; ?>" class="add-item-btn button">Add item</a>
                    </div>
                    <?php if (!empty($items)): ?>
                        <?php foreach ($items[$category->id] as $item): ?>
                            <div class="row">
                                <div class="inputs-left">
                                    <input type="hidden" name="id[<?php print $category->id; ?>][]" value="<?php print $item->id; ?>" />
                                    <label>Title:</label>
                                    <input type="text" name="title[<?php print $category->id; ?>][]" value="<?php print $item->title; ?>"/>
                                    <label>Url:</label>
                                    <input type="text" name="url[<?php print $category->id; ?>][]" value="<?php print $item->url; ?>"/>
                                    <label>New window:</label>
                                    <?php if ($item->new_window): ?>
                                        <input type="checkbox" class="nw" name="nw[<?php print $category->id; ?>][]" checked="checked" value="<?php print $item->new_window; ?>"/>
                                    <?php else: ?>
                                        <input type="checkbox" class="nw" name="nw[<?php print $category->id; ?>][]" value="<?php print $item->new_window; ?>"/>
                                    <?php endif; ?>
                                    <input type="hidden" name="hnw[<?php print $category->id; ?>][]" value="<?php print $item->new_window; ?>" />
                                </div>
                                <div class="delete-current-row"></div>
                            </div>
                        <?php endforeach; ?>
                    <?php else: ?>
                        <div class="row">
                            <input type="hidden" name="id[<?php print $category->id; ?>][]" value="0" />
                            <label>Title:</label>
                            <input type="text" name="title[<?php print $category->id; ?>][]" value=""/>
                            <label>Url:</label>
                            <input type="text" name="url[<?php print $category->id; ?>][]" value=""/>
                            <label>New window:</label>
                            <input type="checkbox" class="nw" name="nw[<?php print $category->id; ?>][]" checked="checked" value="1"/>
                            <input type="hidden" name="hnw[<?php print $category->id; ?>][]" value="1" />
                        </div>
                    <?php endif; ?>
                </div>
            <?php endforeach; ?>
        </div>
        <div class="submit-btn">
            <input type="hidden" name="save" value="0" />
            <a href="#" class="button" id="submit-form">Save</a>
            <a href="/admin/zoomdojo/tablet-panel/tabs" class="button">Cancel</a>
            <a href="/admin/structure/block/manage/zoomdojo_blocks/zoomdojo_blocks_<?php print $bid; ?>/configure" target="_blank" class="button">Configure view area</a>
        </div>
    </form>
</div>

<script type="text/x-template" id="tab-new-content">
    <div class="add-item">
        <a href="#" data-cid="<%= cid %>" class="add-item-btn button">Add item</a>
    </div>
    <div class="row">
        <input type="hidden" name="id[<%= cid %>][]" value="0" />
        <label>Title:</label>
        <input type="text" name="title[<%= cid %>][]" value=""/>
        <label>Url:</label>
        <input type="text" name="url[<%= cid %>][]" value=""/>
        <label>New window:</label>
        <input type="checkbox" class="nw" name="nw[<%= cid %>][]" checked="checked" value="1"/>
        <input type="hidden" name="hnw[<%= cid %>][]" value="1" />
    </div>
</script>

<script type="text/x-template" id="tab-new-row">
    <div class="row">
        <div class="inputs-left">
            <input type="hidden" name="id[<%= cid %>][]" value="0" />
            <label>Title:</label>
            <input type="text" name="title[<%= cid %>][]" value=""/>
            <label>Url:</label>
            <input type="text" name="url[<%= cid %>][]" value=""/>
            <label>New window:</label>
            <input type="checkbox" class="nw" name="nw[<%= cid %>][]" checked="checked" value="1"/>
            <input type="hidden" name="hnw[<%= cid %>][]" value="1" />
        </div>
        <div class="delete-current-row"></div>
    </div>
</script>

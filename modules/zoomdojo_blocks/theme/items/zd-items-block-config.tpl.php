<div id="items-wrapper">
    <div id="dialog" title="Select category">
        <select id="select-category">
            <?php foreach ($allCategories as $category): ?>
                <option value="<?php print $category->id; ?>"><?php print $category->title; ?></option>
            <?php endforeach; ?>
        </select>
    </div>

    <a href="#" class="button" id="add_tab">Add category</a>
    <form method="POST" id="send-items-data-form">
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
                        <table class="table-items" id="tabs-table-<?php print $category->id; ?>">
                            <tbody>
                                <?php foreach($items[$category->id] as $item): ?>
                                    <tr>
                                        <td>item:</td>
                                        <td>
                                            <textarea name="item[<?php print $category->id; ?>][]" class="item-textarea-multy"><?php print $item->item; ?></textarea>
                                            <input type="hidden" name="id[<?php print $category->id; ?>][]" value="<?php print $item->id; ?>" />
                                        </td>
                                        <td>
                                            <div class="delete-current-row"></div>
                                            <input type="hidden" name="weight[<?php print $category->id; ?>][]" class="weight-input" value="<?php print $item->weight; ?>" />
                                        </td>
                                    </tr>
                                <?php endforeach; ?>
                            </tbody>
                        </table>
                    <?php else: ?>
                        <table class="table-items" id="tabs-table-<?php print $category->id; ?>">
                            <tbody>
                                <tr>
                                    <td>item:</td>
                                    <td>
                                        <textarea name="item[<?php print $category->id; ?>][]" class="item-textarea-multy"></textarea>
                                        <input type="hidden" name="id[<?php print $category->id; ?>][]" value="0" />
                                    </td>
                                    <td>
                                        <div class="delete-current-row"></div>
                                        <input type="hidden" name="weight[<?php print $category->id; ?>][]" class="weight-input" value="0" />
                                    </td>
                                </tr>
                            </tbody>
                        </table>
                    <?php endif; ?>
                </div>
            <?php endforeach; ?>
        </div>
        <div class="submit-btn">
            <input type="hidden" name="save" value="0" />
            <a href="#" class="button" id="submit-form">Save</a>
            <a href="/admin/zoomdojo/items-block/blocks" class="button">Cancel</a>
            <a href="/admin/structure/block/manage/zoomdojo_blocks/zoomdojo_blocks_<?php print $bid; ?>/configure" target="_blank" class="button">Configure view area</a>
        </div>
    </form>
</div>

<script type="text/x-template" id="tab-new-content">
    <div class="add-item">
        <a href="#" data-cid="<%= cid %>" class="add-item-btn button">Add item</a>
    </div>
    <table class="table-items" id="tabs-table-<%= cid %>">
        <tbody>
            <tr>
                <td>item:</td>
                <td>
                    <textarea name="item[<%= cid %>][]" class="item-textarea-multy"></textarea>
                    <input type="hidden" name="id[<%= cid %>][]" value="0" />
                </td>
                <td>
                    <div class="delete-current-row"></div>
                    <input type="hidden" name="weight[<%= cid %>][]" class="weight-input" value="0" />
                </td>
            </tr>
        </tbody>
    </table>
</script>

<script type="text/x-template" id="tab-new-row">
    <tr>
        <td>item:</td>
        <td>
            <textarea name="item[<%= cid %>][]" class="item-textarea-multy"></textarea>
            <input type="hidden" name="id[<%= cid %>][]" value="0" />
        </td>
        <td>
            <div class="delete-current-row"></div>
            <input type="hidden" name="weight[<%= cid %>][]" class="weight-input" value="<%= weight %>" />
        </td>
    </tr>
</script>
